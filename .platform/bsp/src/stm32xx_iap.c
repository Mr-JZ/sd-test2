/*
 * $Id$     lpc17xx_iap.c
 * @file	lpc17xx_iap.c
 *
 * @brief	contains internal flash in-application-programming routines
 *
 * @version	1.0
 * @date		20.07.2015
 * @author Wuebbelmann
 */

#include <string.h>
#ifdef DEBUG
#include <stdio.h>
#endif
#include "chip.h"
#include "stm32xx_iap.h"



#ifndef __cplusplus
#ifndef bool      // might be defined in stdbool.h,
typedef enum _bool {true = 1==1, false = !true} bool;
#endif
#endif



typedef enum _Banks_e
{
	Bank1,
	Bank2,
	InvalidBank
} Bank_e;


#define FS_1MB   1
#define FS_512KB 2
#define FS_256KB 3

// Set FLASHSIZE to the correct value!!!!
#define FLASHSIZE FS_1MB
//#define FLASHSIZE FS_512KB
//#define FLASHSIZE FS_256KB
#if (!defined(FLASHSIZE) ||  \
     (defined(FLASHSIZE) && (FLASHSIZE != FS_1MB && FLASHSIZE != FS_512KB && FLASHSIZE != FS_256KB)))
#error Please define flash size!!!
#endif


// local variables:
#if (FLASHSIZE == FS_1MB)
static const uint32_t PAGESPERBANK = 256;
#elif ((FLASHSIZE == FS_512KB))
static const uint32_t PAGESPERBANK = 128;
#elif ((FLASHSIZE == FS_256KB))
static const uint32_t PAGESPERBANK =  64;
#endif



static const uint32_t FIRSTPAGEBANK1 = 0;
static const uint32_t FIRSTPAGEBANK2 = 256;
static const uint32_t SIZEOFPAGE     = PAGESIZE;
static const uint32_t STARTADDRESSBANK1 = 0;
static const uint32_t STARTADDRESSBANK2 = STARTADDRESSBANK1+PAGESPERBANK*SIZEOFPAGE;
static const uint32_t ENDADDRESSBANK1 = STARTADDRESSBANK2 -1;
static const uint32_t ENDADDRESSBANK2 = STARTADDRESSBANK2+PAGESPERBANK*SIZEOFPAGE -1;
static const uint32_t MAXPAGENUM     = FIRSTPAGEBANK2 + PAGESPERBANK -1;


static bool isInit = false;




// local functions
static bool iapInit()
{

	isInit  = true;
	return isInit;
}


static bool unlockFlash()
{
	return HAL_OK == HAL_FLASH_Unlock();
}

static bool lockFlash()
{
	return HAL_OK == HAL_FLASH_Lock();
}


static uint32_t getPageFromAddress(void *addr)
{
    uint32_t address      = (uint32_t) addr;
    uint32_t pageNumber = UINT32_MAX;

    if (address >= STARTADDRESSBANK1 && address < ENDADDRESSBANK2)
    {
        pageNumber = (address-STARTADDRESSBANK1) / SIZEOFPAGE;
        if(pageNumber >= PAGESPERBANK) // we are in Bank2
        {
        	pageNumber = pageNumber - PAGESPERBANK + FIRSTPAGEBANK2;
         }
    }
    return pageNumber;
}


static Bank_e getBankFromAddress(void *addr)
{
	Bank_e bank = InvalidBank;
    uint32_t address      = (uint32_t) addr;

    if (address >= STARTADDRESSBANK1 && address <= ENDADDRESSBANK1)
    {
    	bank = Bank1;
    }
    else if (address >= STARTADDRESSBANK2 && address <= ENDADDRESSBANK2)
    {
    	bank = Bank2;
    }
    return bank;
}



static IAPErrorCode checkParams(void *source, void * destination, uint32_t length)
{
	IAPErrorCode  xcode = FLASH_SUCCESS;
	uint32_t startPage = getPageFromAddress(destination);
	uint32_t endPage   = getPageFromAddress(destination + length);

	if (!isInit)
    {
    	iapInit();
    }

	// parameter check
	if ((uint32_t)destination & 0x7)  xcode = INVALID_DSTALIGNMENT;  // 8 Byte alignment
	//if ((uint32_t)source      & 0x7)  xcode = INVALID_SRCALIGNMENT;  // 8 Byte alignment
	if (!length)                      xcode = INVALID_LENGTH;
    if (ENDADDRESSBANK2 < (uint32_t)destination + length)
    	                              xcode = INVALID_LENGTH;
	if (MAXPAGENUM < startPage || MAXPAGENUM < endPage)
		                              xcode =  INVALID_ADDRESS;

	// make sure, that program code is not in same bank as destination
	if (getBankFromAddress(HAL_FLASH_Program) == getBankFromAddress(destination))
		                              xcode = INVALID_ADDRESS;
	if (getBankFromAddress(HAL_FLASH_Program) == getBankFromAddress(destination+length))
			                          xcode = INVALID_ADDRESS;

	if (getBankFromAddress(HAL_FLASHEx_Erase) == getBankFromAddress(destination))
                                      xcode = INVALID_ADDRESS;


#ifdef DEBUG
	if (FLASH_SUCCESS != xcode)
	{
        fprintf(stderr,"*** %s %d flash parameter check failed!\n", __FILE__, __LINE__);
	}
#endif
    return xcode;
}




IAPErrorCode iap_write2Flash(void *source, void * destination, uint32_t length)
{
	IAPErrorCode xcode = FLASH_SUCCESS;

	// parameter check
	xcode = checkParams(source, destination, length);
	if (FLASH_SUCCESS != xcode)  return xcode;

	uint64_t *mSrc  = (uint64_t *)  source;
	uint64_t *mDest  = (uint64_t *) destination;

	// copy Data in Flash:
	if (!unlockFlash()) return UNKNOWN_ERROR;
    while (length)
    {
    	uint64_t data = *mSrc;
    	uint64_t cData = *mDest;
    	 HAL_StatusTypeDef stat = HAL_OK;
    	if (cData == ERASECHAR)
    	{
    	    stat = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, (uint32_t)mDest, data);
     	    ++mSrc;
    	    ++mDest;
    	}
    	else
    	{
    		xcode = WRITE_ERROR;
#ifdef DEBUG
            fprintf(stderr,"*** %s %d try to write not erased flash address!\n", __FILE__, __LINE__);
#endif
    	}
    	if (length >= sizeof(uint64_t))
    	{
    		length -= sizeof(uint64_t);
    	}
    	else
    	{
    		length = 0;
    	}
    	if(stat != HAL_OK || FLASH_SUCCESS != xcode)
    	{
    		length = 0;  // stop loop
    		xcode = WRITE_ERROR;
#ifdef DEBUG
            fprintf(stderr,"*** %s %d error Flash write failed!\n", __FILE__, __LINE__);
#endif
    	}
    }
    lockFlash();
	return xcode;
}


IAPErrorCode iap_eraseFlash(void * destination, uint32_t length)
{
	IAPErrorCode xcode = FLASH_SUCCESS;

	// parameter check
	xcode = checkParams(0, destination, length);
	if (FLASH_SUCCESS != xcode)  return xcode;


	uint32_t startPage = getPageFromAddress(destination);

	FLASH_EraseInitTypeDef eraseDefinition;
	eraseDefinition.Banks     = 0; // don't care when page erase
	eraseDefinition.NbPages   = length;
	eraseDefinition.Page      = startPage;
	eraseDefinition.TypeErase = FLASH_TYPEERASE_PAGES;

	uint32_t PageError;
    // erase command:
	if (!unlockFlash()) return UNKNOWN_ERROR;
	HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&eraseDefinition, &PageError);
    lockFlash();
    if (HAL_OK != status)
    {
    	xcode = ERASE_ERROR;
#ifdef DEBUG
        fprintf(stderr,"*** %s %d error Flash erase failed!\n", __FILE__, __LINE__);
#endif

    }
    return xcode;

}

uint32_t iap_getSegmentStartAddress(uint32_t page)
{
	uint32_t address = ILLEGAL_ADDRESS;
	if (FIRSTPAGEBANK1 + PAGESPERBANK > page) // page is in bank1
	{
		address = STARTADDRESSBANK1 + (page - FIRSTPAGEBANK1)*SIZEOFPAGE;
	}
	else
	if(FIRSTPAGEBANK2 <= page &&
	   FIRSTPAGEBANK2 + PAGESPERBANK > page)
	{
		address = STARTADDRESSBANK2 + (page - FIRSTPAGEBANK2)*SIZEOFPAGE;
	}
	return address;
}

uint32_t iap_getSegmentSize(uint32_t page)
{
	uint32_t size = ILLEGAL_ADDRESS;
    if (iap_getSegmentStartAddress(page) != ILLEGAL_ADDRESS)
    {
    	size = SIZEOFPAGE;
    }
	return size;
}



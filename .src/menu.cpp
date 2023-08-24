/*
 * menu.cpp
 *
 *  Created on: 24.10.2016
 *      Author: Wuebbelmann
 */
//#include <cstring>

#include <menu.h>

#define JOYSTICK_UP               Platform::BSP::STM32Facade::BaseBoard8
#define JOYSTICK_DOWN             Platform::BSP::STM32Facade::BaseBoard10
#define JOYSTICK_LEFT             Platform::BSP::STM32Facade::BaseBoard6
#define JOYSTICK_RIGHT            Platform::BSP::STM32Facade::BaseBoard9
#define JOYSTICK_PRESS            Platform::BSP::STM32Facade::BaseBoard7

#define MULT10                    Platform::BSP::STM32Facade::BaseBoard1
#define MULT100                   Platform::BSP::STM32Facade::BaseBoard49

#ifdef OLED
char memOled[sizeof(DISPLAY)];
#endif

#ifdef MENUETASK
#define UPEVENT     (0x1 << 4)
#define DOWNEVENT   (0x1 << 5)
#define LEFTEVENT   (0x1 << 6)
#define RIGHTEVENT  (0x1 << 7)
#define PRESSEVENT  (0x1 << 8)
#define ALLEVENTS   (UPEVENT | DOWNEVENT  | LEFTEVENT  | RIGHTEVENT  | PRESSEVENT)

osThreadId MenuTask::s_threadId = nullptr;
#endif

// class static members
Platform::BSP::DigitalIn Menu::m_mul10(MULT10);
Platform::BSP::DigitalIn Menu::m_mul100(MULT100);
#ifdef OLED
DISPLAY *Menu::oled = nullptr;
#endif

Menu *Menu::activeMenu = nullptr;

// Interrupt functions
static void intUp(Platform::BSP::DigitalInterrupt::EdgeType v) {
#ifdef MENUETASK
	osSignalSet(MenuTask::getTaskId(), UPEVENT);
#else
    if(Menu::getActiveMenu())
    {
        Menu::getActiveMenu()->incrementActiveItem();
        Menu::getActiveMenu()->printMenu();
    }
#endif
}

static void intDown(Platform::BSP::DigitalInterrupt::EdgeType v) {
#ifdef MENUETASK
	osSignalSet(MenuTask::getTaskId(), DOWNEVENT);
#else
    if(Menu::getActiveMenu())
    {
        Menu::getActiveMenu()->decrementActiveItem();
        Menu::getActiveMenu()->printMenu();
    }
#endif
}

static void intPress(Platform::BSP::DigitalInterrupt::EdgeType v) {
#ifdef MENUETASK
	osSignalSet(MenuTask::getTaskId(), PRESSEVENT);
#else
    if(Menu::getActiveMenu())
    {
        Menu::getActiveMenu()->handlePress();
    }
#endif
}

static void intRight(Platform::BSP::DigitalInterrupt::EdgeType v) {
#ifdef MENUETASK
	osSignalSet(MenuTask::getTaskId(), RIGHTEVENT);
#else
    if(Menu::getActiveMenu())
    {
        Menu::getActiveMenu()->onRight();
    }
#endif
}

static void intLeft(Platform::BSP::DigitalInterrupt::EdgeType v) {
#ifdef MENUETASK
	osSignalSet(MenuTask::getTaskId(), LEFTEVENT);
#else
    if(Menu::getActiveMenu())
    {
        Menu::getActiveMenu()->onLeft();
    }
#endif
}

Menu::Menu(Menu *parent) :
		m_parent(parent), m_activeItem(0), m_size(0), m_menu(nullptr), m_isDynamicMem(
				false) {
	initInput();
	initOutput();
}

Menu::~Menu() {
	if (m_isDynamicMem)
		delete[] m_menu;
}

void Menu::initOutput() {
#ifdef OLED
	if (nullptr == oled) {
		oled = new (memOled) DISPLAY(
				Platform::BSP::STM32Facade::instance(
						Platform::BSP::STM32Facade::I2C_Peripheral::UseI2C1));
		oled->initialize(128);

		oled->showDemoPicture();
	}
#endif
}

void Menu::initInput() {
	static bool isInit = false;
	if (!isInit) {
		Platform::BSP::DigitalInterrupt up(JOYSTICK_UP);
		Platform::BSP::DigitalInterrupt down(JOYSTICK_DOWN);
		Platform::BSP::DigitalInterrupt left(JOYSTICK_LEFT);
		Platform::BSP::DigitalInterrupt right(JOYSTICK_RIGHT);
		Platform::BSP::DigitalInterrupt press(JOYSTICK_PRESS);

//       NVIC_SetPriority(EINT3_IRQn, 6);       // higher then configMAX_SYSCALL_INTERRUPT_PRIORITY!

		up.onInterrupt(intUp,
				Platform::BSP::DigitalInterrupt::EdgeType::FALLING_EDGE);
		down.onInterrupt(intDown,
				Platform::BSP::DigitalInterrupt::EdgeType::FALLING_EDGE);
		press.onInterrupt(intPress,
				Platform::BSP::DigitalInterrupt::EdgeType::FALLING_EDGE);
		right.onInterrupt(intRight,
				Platform::BSP::DigitalInterrupt::EdgeType::FALLING_EDGE);
		left.onInterrupt(intLeft,
				Platform::BSP::DigitalInterrupt::EdgeType::FALLING_EDGE);

		isInit = true;
	}
}

void Menu::setMenu(const Entry_t *men, size_t size, void *memPtr) {
	m_size = size / sizeof(Entry_t);
	if (!memPtr) {
		m_menu = new Entry_t[m_size];
		m_isDynamicMem = true;
	} else {
		m_menu = new (memPtr) Entry_t[m_size];
		m_isDynamicMem = false;
	}
	for (size_t i = 0; i < m_size; ++i) {
		m_menu[i] = men[i];
		m_menu[i].marker = ' ';
		if (m_menu[i].mfunction != nullptr) {
			m_activeItem = i;
		}
	}
	m_menu[m_activeItem].marker = '>';
}

void Menu::incrementActiveItem() {
	uint8_t count = 0;
	m_menu[m_activeItem].marker = ' ';
	do {
		++m_activeItem;
		m_activeItem %= m_size;
		++count;
	} while (m_menu[m_activeItem].mfunction == nullptr && count < m_size);
	m_menu[m_activeItem].marker = '>';
}

void Menu::decrementActiveItem() {
	uint8_t count = 0;
	m_menu[m_activeItem].marker = ' ';
	do {
		if (m_activeItem) {
			--m_activeItem;
		} else {
			m_activeItem = m_size - 1;
		}
		++count;
	} while (m_menu[m_activeItem].mfunction == nullptr && count < m_size);
	m_menu[m_activeItem].marker = '>';
}

void Menu::handlePress() {
	Mfunction func = m_menu[m_activeItem].mfunction;
	if (func) {
		(activeMenu->*func)(nullptr, m_menu);
	}
}

void Menu::menuUp(void *value, Entry_t *menuEntry) {
	if (m_parent) {
		m_parent->beActive();
	}
	activeMenu->printMenu();
}

void Menu::printMenu() const {
	clrscr();
	for (size_t i = 0; i < m_size; ++i) {
		char text[30];
		snprintf(text, sizeof(text), "%c%s\n", m_menu[i].marker,
				m_menu[i].mtext);
		print(text);
	}
#ifdef OLED
	oled->flush();
#endif
}

// Task!
#ifdef MENUETASK
MenuTask::MenuTask(Menu &startMenu) :
		RTOS::Task("MenueTask", 1000, osPriorityBelowNormal), m_startMenu(
				startMenu) {
	s_threadId = m_handle;
	m_startMenu.beActive();
}

void MenuTask::m_task() {
	while (1) {
		osEvent event = osSignalWait(ALLEVENTS | RTOS::SIGNALEVENT,
				osWaitForever);
		if (event.status == osEventSignal) {
			if (Menu::getActiveMenu())   // only if we have an active menu!
			{
				if (event.value.signals & UPEVENT) {
					Menu::getActiveMenu()->onUp();
				}
				if (event.value.signals & DOWNEVENT) {
					Menu::getActiveMenu()->onDown();
				}
				if (event.value.signals & PRESSEVENT) {
					Menu::getActiveMenu()->handlePress();
				}
				if (event.value.signals & RIGHTEVENT) {
					Menu::getActiveMenu()->onRight();
				}
				if (event.value.signals & LEFTEVENT) {
					Menu::getActiveMenu()->onLeft();
				}
				if (event.value.signals & RTOS::SIGNALEVENT) {
					Menu::getActiveMenu()->printMenu();
				}
			}
		}
	}
}

#endif

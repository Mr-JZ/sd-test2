/*
 * Regler.h
 *
 *  Created on: 26.10.2016
 *      Author: Wuebbelmann
 */

#ifndef REGLER_H_
#define REGLER_H_

#include <cstdint>

/**
 * \class Regler
 *  Abstract base class of controller
 * \brief defines an interface method operator()  in which control algorithms can be implemented \n
 *        by derived classes
 *
 */
template<typename T>
class Regler {
public:
     /**
      *  \brief constructor
      *
      *  \param [in] grad dimension of parameter
      *  \param [in] limit max. value of set output.
      *  \param [in] mem: memory for control parameters. If nullptr, dynamic memory is allocated
      *  \return
      *
      *  \details
      */
    Regler(uint32_t grad, T limit = 100, T* mem = nullptr);
     /**
      *  \brief destructor
      *
      *  \return Return_Description
      *
      *  \details Details
    */
    virtual ~Regler();

    virtual T operator()(T ist, T soll) = 0;

    /**
     * \brief get parameter
     * \param index index of parameter to get
     * \return reference to parameter or error
     */
    T& getParameter(uint32_t index) {if (index < m_grad) return m_param[index]; return m_error;}

    /**
     * \brief get number of parameter of control
     * \return grad
     */
    uint32_t getGrad() const { return m_grad;};

protected:
    uint32_t  m_grad;
    T*        m_param;
    T         m_error;
    uint32_t  m_divider;
    T         m_limit;
    bool      m_isDynamic;
};



template<typename T>
Regler<T>::Regler(uint32_t grad, T limit, T* mem):
   m_grad(grad),
   m_divider(10),
   m_limit(limit),
   m_isDynamic(true)
{
    if (nullptr != mem)
    {
        m_param = mem;
        m_isDynamic = false;
    }
    else
    {
        m_param = new T[m_grad];
    }
}

template<typename T>
Regler<T>::~Regler()
{
    if (m_isDynamic) delete [] m_param;
}


// implementation of controller:

/**
 * \class Pidregler
 * \brief implements a PID controller
 *
 */

template<typename T>
class Pidregler :public Regler<T>
{
public:
     Pidregler(T q0, T q1, T q2, T* mem = nullptr);
     T operator()(T ist, T soll) override;
private:
     T m_yalt;
     T m_ealt;
     T m_ealt2;
};


template<typename T>
Pidregler<T>::Pidregler(T q0, T q1, T q2, T* mem) :
  Regler<T>(3,0x2580, mem),  // max. set value of PWM at 10kHz
  m_yalt(0),
  m_ealt(0),
  m_ealt2(0)

{
  Regler<T>::m_param[0] = q0;
  Regler<T>::m_param[1] = q1;
  Regler<T>::m_param[2] = q2;
}

template<typename T>
T Pidregler<T>::operator()(T ist, T soll)
{
    T e = soll-ist;
    T reg =  Regler<T>::m_param[0] * e
           + Regler<T>::m_param[1] * m_ealt
           + Regler<T>::m_param[2] * m_ealt2
           + (1 << (Regler<T>::m_divider -1));   // round up if required
    reg /= (1 << Regler<T>::m_divider);          // no right shift in case we have float data type

    T y = m_yalt + reg;

    m_ealt2  = m_ealt;
    m_ealt   = e;

    // adapt to Limits
    if ( y < 0) y = 0;
    if ( y > Regler<T>::m_limit) y = Regler<T>::m_limit;
    m_yalt   = y;

    return y;
}


#endif /* REGLER_H_ */

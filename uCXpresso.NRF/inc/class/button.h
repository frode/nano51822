/*
 ===============================================================================
 Name        : button
 Author      : uCXpresso
 Version     : v1.0.1
 Date		 : 2014/12/1
 Description : Implement a button input with bounce detected.
 ===============================================================================
 History
 ---------+---------+--------------------------------------------+-------------
 DATE     |	VERSION |	DESCRIPTIONS							 |	By
 ---------+---------+--------------------------------------------+-------------
 2014/11/14	v1.0.0	First Edition									Jason
 2014/12/1	v1.0.1	Add weakup option in constructor.				Jason
 ===============================================================================
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <class/pin.h>
#include <class/timeout.h>

/**
 * @brief Button actions.
 * @ingroup Enumerations
 */
enum BTN_ACTION_T {
	BTN_ACT_LOW = LOW,		///< High to Low
	BTN_ACT_HIGH = HIGH		///< Low to High
};

/**
 * @brief Button event
 * @ingroup Enumerations
 */
enum  BTN_EVENT_T{
	BTN_NOTHING = 0,
	BTN_PRESSED,
	BTN_RELEASED
};

/**
 * @brief CButton class provides a debounce button service.
 * @class CButton button.h "class/button.h"
 * @note The CButton is a static class.
 * @ingroup Peripherals
 */
class CButton: public CPin {
public:
	/**
	 * @brief Constructs the CButton class.
	 * @param pin 		Indicates the pin number to connect to the CButton object.
	 * @param action 	Specifies the  @ref BTN_ACTION_T of button.
	 * @param mode		Specifies the pull mode of the pin.
	 * @param forWakeup Set the pin can weakup the system from power off mode.
	 */
	CButton(uint8_t pin, BTN_ACTION_T action=BTN_ACT_LOW, PIN_INPUT_MODE_T mode=INTERNAL_PULL_UP, bool forWeakup=true);

	/**
	 * @brief Poll the button event.
	 * @return
	 * @retval BTN_NOTHING	The Button does nothing.
	 * @retval BTN_PRESSED	The Button pressed.
	 * @retval BTN_RELEASED	The button released.
	 *
	 * @code
	 * 	CButton btn(17);	// Connect btn object to P0.17
	 * 	switch( btn.isPressed() ) {
	 * 	case BTN_PRESSED:
	 * 		led = LED_ON;
	 * 		break;
	 * 	case BTN_RELEASED:
	 * 		led = LED_OFF;
	 * 		break;
	 * 	case BTN_NOTHING:
	 * 		break;
	 * 	}
	 * @endcode
	 */
	virtual BTN_EVENT_T isPressed();

	/**
	 * @brief set bounce timeout (default 10ms) in millisecond.
	 */
	inline void bounce_timeout(uint16_t ms) {
		m_bounce_timeout = ms;
	}

	//
	///@cond
	//
protected:
	CTimeout 		m_tmBounce;
	uint32_t		m_bounce_timeout;
	PIN_LEVEL_T 	m_action;
	PIN_LEVEL_T 	m_lastState;
	///@endcond
};

/**\example /ble/ble_app_hid_keyboard/src/main.cpp
 * This is an example of how to use the CButton class.
 * More details about this example.
 */

#endif /* BUTTON_H_ */

#pragma once
#define SGL_JOYSTICK_1             0
#define SGL_JOYSTICK_2             1
#define SGL_JOYSTICK_3             2
#define SGL_JOYSTICK_4             3
#define SGL_JOYSTICK_5             4
#define SGL_JOYSTICK_6             5
#define SGL_JOYSTICK_7             6
#define SGL_JOYSTICK_8             7
#define SGL_JOYSTICK_9             8
#define SGL_JOYSTICK_10            9
#define SGL_JOYSTICK_11            10
#define SGL_JOYSTICK_12            11
#define SGL_JOYSTICK_13            12
#define SGL_JOYSTICK_14            13
#define SGL_JOYSTICK_15            14
#define SGL_JOYSTICK_16            15
#define SGL_JOYSTICK_LAST          SGL_JOYSTICK_16
/*! @} */

/*! @defgroup gamepad_buttons Gamepad buttons
 *  @brief Gamepad buttons.
 *
 *  See @ref gamepad for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define SGL_GAMEPAD_BUTTON_A               0
#define SGL_GAMEPAD_BUTTON_B               1
#define SGL_GAMEPAD_BUTTON_X               2
#define SGL_GAMEPAD_BUTTON_Y               3
#define SGL_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define SGL_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define SGL_GAMEPAD_BUTTON_BACK            6
#define SGL_GAMEPAD_BUTTON_START           7
#define SGL_GAMEPAD_BUTTON_GUIDE           8
#define SGL_GAMEPAD_BUTTON_LEFT_THUMB      9
#define SGL_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define SGL_GAMEPAD_BUTTON_DPAD_UP         11
#define SGL_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define SGL_GAMEPAD_BUTTON_DPAD_DOWN       13
#define SGL_GAMEPAD_BUTTON_DPAD_LEFT       14
#define SGL_GAMEPAD_BUTTON_LAST            SGL_GAMEPAD_BUTTON_DPAD_LEFT

#define SGL_GAMEPAD_BUTTON_CROSS       SGL_GAMEPAD_BUTTON_A
#define SGL_GAMEPAD_BUTTON_CIRCLE      SGL_GAMEPAD_BUTTON_B
#define SGL_GAMEPAD_BUTTON_SQUARE      SGL_GAMEPAD_BUTTON_X
#define SGL_GAMEPAD_BUTTON_TRIANGLE    SGL_GAMEPAD_BUTTON_Y
 /*! @} */

 /*! @defgroup gamepad_axes Gamepad axes
  *  @brief Gamepad axes.
  *
  *  See @ref gamepad for how these are used.
  *
  *  @ingroup input
  *  @{ */
#define SGL_GAMEPAD_AXIS_LEFT_X        0
#define SGL_GAMEPAD_AXIS_LEFT_Y        1
#define SGL_GAMEPAD_AXIS_RIGHT_X       2
#define SGL_GAMEPAD_AXIS_RIGHT_Y       3
#define SGL_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define SGL_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define SGL_GAMEPAD_AXIS_LAST          SGL_GAMEPAD_AXIS_RIGHT_TRIGGER
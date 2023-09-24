/**
  * @copyright : Copyright (c) 2020 Hu Enrong
  */
#ifndef _GPIO_CFG_H_
#define _GPIO_CFG_H_

#include <stdint.h>

// gpio direction
enum gpio_direction
{
     GPIO_IN = 0,
     GPIO_OUT = 1
};

// gpio level value
enum gpio_value
{
     GPIO_LOW = 0,
     GPIO_HIGH = 1
};

// gpio interrupt input, edge value
enum gpio_edge
{
     GPIO_NONE = 0, // not an interrupt
     GPIO_RISING = 1, //Interrupt input, rising edge
     GPIO_FALLING = 2, //Interrupt input, falling edge
     GPIO_BOTH = 3 //Interrupt input, rising edge and falling edge
};

/**
  * @brief Export gpio to user space
  * @param gpio_num: input parameter, gpio number to be exported
  * @return success: 0
  * Failure: -1
  */
int gpio_export(const uint16_t gpio_num);

/**
  * @brief Cancel gpio exported to user space
  * @param gpio_num: input parameter, the gpio number to be cancelled.
  * @return success: 0
  * Failure: -1
  */
int gpio_unexport(const uint16_t gpio_num);

/**
  * @brief Set gpio direction
  * @param gpio_num: input parameter, gpio number to be set
  * @param direction: input parameter, gpio direction to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_direction(const uint16_t gpio_num,
                        const enum gpio_direction direction);

/**
  * @brief Set the gpio output level value
  * @param gpio_num: input parameter, gpio number to be set
  * @param value: input parameter, gpio level value to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_value(const uint16_t gpio_num, const enum gpio_value value);

/**
  * @brief Get the level value of gpio
  * @param value: gpio level value
  * @param gpio_num: gpio number
  * @return success: 0
  * Failure: -1
  */
int gpio_get_value(enum gpio_value *value, const uint16_t gpio_num);

/**
  * @brief Set gpio trigger edge
  * @param gpio_num: input parameter, gpio number to be set
  * @param edge: input parameter, gpio edge to be set
  * @return success: 0
  * Failure: -1
  */
int gpio_set_edge(const uint16_t gpio_num, const enum gpio_edge edge);

/**
  * @brief Open gpio device
  * @param gpio_num: input parameter, gpio number to be opened
  * @return success: return device file descriptor
  * Failure: -1
  */
int gpio_open(const uint16_t gpio_num);

/**
  * @brief Close gpio device
  * @param fd: input parameter, device file descriptor to be closed
  * @return success: 0
  * Failure: -1
  */
int gpio_close(const int fd);
#endif
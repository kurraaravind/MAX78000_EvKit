/******************************************************************************
 *
 * Copyright (C) 2022-2023 Maxim Integrated Products, Inc. All Rights Reserved.
 * (now owned by Analog Devices, Inc.),
 * Copyright (C) 2023 Analog Devices, Inc. All Rights Reserved. This software
 * is proprietary to Analog Devices, Inc. and its licensors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

/***** Includes *****/
#include "test_gpio.h"
#include "gpio1.h"


/******************************************************************************/
int test_gpio_set(void)
{
	gpio_set(PORT,PIN2,VALUE0);
	if(gpio_get(PORT,PIN2)==VALUE0)
	{
		return PASS;
	}
	else
	{
		return FAIL;
	}
}
/******************************************************************************/
int test_gpio_get(void)
{
	gpio_set(PORT,PIN3,VALUE1);
	if(gpio_get(PORT,PIN3)==VALUE1)
	{
		return PASS;
	}
	else
	{
		return FAIL;
	}
}
/******************************************************************************/
int test_gpio_toggle(void)
{
	int c=0;
	gpio_set(PORT,PIN2,VALUE0);
	if(gpio_get(PORT,PIN2)==VALUE0)
	{
		c++;
	}
	else
	{
		return FAIL;
	}

	gpio_set(PORT,PIN2,VALUE1);
	if(gpio_get(PORT,PIN2)==VALUE1)
	{
		return c++;
	}
	else
	{
		return FAIL;
	}
	
	gpio_set(PORT,PIN2,VALUE0);
	if(gpio_get(PORT,PIN2)==VALUE0)
	{
		return c++;
	}
	else
	{
		return FAIL;
	}

	gpio_set(PORT,PIN2,VALUE1);
	if(gpio_get(PORT,PIN2)==VALUE1)
	{
		return c++;
	}
	else
	{
		return FAIL;
	}
	if(c == 4)
	{
		return PASS;
	}
	else
	{
		return FAIL;
	}
}
/******************************************************************************/
void test_gpio(void)
{
	int a = test_gpio_set();
	int b = test_gpio_get();
	int c = test_gpio_toggle();
	if(a == PASS && b == PASS && C == PASS)
	{
		printf("Test cases of GPIO PASSED!\n");
	}
	else
	{
		printf("Test cases of GPIO FAILED!\n");
	}
}

/******************************************************************************/

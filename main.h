/*!
 * @file
 * @section LICENSE
 * Copyright 2021 Conner Macolley
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 * 
 * @section DESCRIPTION
 * Describe functions for @file main.c
 */



#ifndef __MAIN_NPSI_H
#define __MAIN_NPSI_H

int main(int, char **);

void sigint_processor(int);
static void print_help_and_exit();

#endif /* __MAIN_NPSI_H */
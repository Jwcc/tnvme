/*
 * Copyright (c) 2011, Intel Corporation.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#ifndef _IO_H_
#define _IO_H_

#include "tnvme.h"
#include "../Queues/sq.h"
#include "../Queues/cq.h"


/**
* This class is meant not be instantiated because it should only ever contain
* static members. These utility functions can be viewed as wrappers to
* perform common, repetitious tasks which avoids coping the same chunks of
* code throughout the framework.
*
* @note This class may throw exceptions, please see comment within specific
*       methods.
*/
class IO
{
public:
    IO();
    virtual ~IO();

    /**
     * Send an existing, user defined cmd to hdw using the specific SQ/CQ pairs.
     * @note Throws upon errors
     * @note Method uses pre-existing values of CC.IOCQES
     * @param grpName Pass the name of the group to which this test belongs
     * @param testName Pass the name of the child testclass
     * @param ms Pass the max number of ms to wait until numTil CE's arrive.
     * @param sq Pass pre-existing SQ to issue a cmd into
     * @param cq Pass pre-existing CQ to reap CE to verify successful creation
     * @param cmd Pass the cmd to issue into the supplied CQ
     * @param qualify Pass a qualifying string to append to each dump file
     * @param verbose Pass true to dump resources to dump files, otherwise false
     */
    static void SendCmdToHdw(string grpName, string testName, uint16_t ms,
        SharedSQPtr sq, SharedCQPtr cq, SharedCmdPtr cmd, string qualify,
        bool verbose);


private:
    static void ReapCE(SharedCQPtr cq, uint16_t numCE,  uint32_t &isrCount,
        string grpName, string testName, string qualify);
};


#endif
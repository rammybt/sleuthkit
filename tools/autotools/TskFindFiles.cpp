/*
** The Sleuth Kit
**
** Brian Carrier [carrier <at> sleuthkit [dot] org]
** Copyright (c) 2010-2019 Brian Carrier.  All Rights reserved
**
** This software is distributed under the Common Public License 1.0
**
*/

/**
* \file TskFindFiles.cpp
* Contains C++ code that creates the Find Files class.
*/

#include <shlwapi.h>
#include <string>
#include <sstream>
#include <sstream>
#include <locale>
#include <iomanip>

#include "LogicalImagerRuleSet.h"
#include "tsk/tsk_tools_i.h"
#include "TskFindFiles.h"

/**
 * Create the Find Files object given the Logical Imager Configuration
 * @param config LogicalImagerRuleSet to use for finding files
 */
TskFindFiles::TskFindFiles(const LogicalImagerRuleSet *ruleSet, const char *alertFilePath) {
    m_logicialImagerRuleSet = ruleSet;
    m_alertFilePath.assign(alertFilePath);
    m_alertFile = fopen(alertFilePath, "w");
    if (!m_alertFile) {
        fprintf(stderr, "ERROR: Failed to open alert file %s\n", alertFilePath);
        exit(1);
    }
    fprintf(m_alertFile, "Extraction Status\tDescription\tFilename\tPath\n");
}

TskFindFiles::~TskFindFiles() {
    if (m_alertFile) {
        fclose(m_alertFile);
    }
}

TskFindFiles::~TskFindFiles() {
}

/**
 * Print errors as they are encountered
 */
uint8_t TskFindFiles::handleError() {
    fprintf(stderr, "%s", tsk_error_get());
    return 0;
}

/**
* Process a file. If the file matches a rule specified in the LogicalImagerRuleSet,
* we collect it by reading the file content.
* @param fs_file File details
* @param path Full path of parent directory
* @returns TSK_OK or TSK_ERR. All error must have been registered.
*/
TSK_RETVAL_ENUM TskFindFiles::processFile(TSK_FS_FILE *fs_file, const char *path) {
    return m_logicialImagerRuleSet->processFile(fs_file, path);
}
#ifndef ELENGINEDEFINITIONS_H_
#define ELENGINEDEFINITIONS_H_

#include <iostream>
#include "ELDefinitions.h"

#define EL_STR_ERROR "EL_ERROR: "
#define EL_STR_WARNING "EL_WARNING: "
#define EL_STR_INFO "EL_INFO: "

#define EL_CC_ERROR_LOG(ERROR) std::cerr << EL_STR_ERROR << ERROR
#define EL_CC_ERROR_LOG_VARS(ERROR, ...) std::cerr << EL_STR_ERROR << el_string(ERROR, __VA_ARGS__)

#define EL_CC_WARNING_LOG(WARNING) std::cerr << EL_STR_WARNING << WARNING
#define EL_CC_WARNING_LOG_VARS(WARNING, ...) std::cerr << EL_STR_WARNING << el_string(WARNING, __VA_ARGS__)

#define EL_CC_INFO_LOG(INFO) std::cerr << EL_STR_INFO << INFO
#define EL_CC_INFO_LOG_VARS(INFO, ...) std::cerr << EL_STR_INFO << el_string(INFO, __VA_ARGS__)

#endif // ELENGINEDEFINITIONS_H_

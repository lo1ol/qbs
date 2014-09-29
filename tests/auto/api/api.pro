TARGET = tst_api

HEADERS = tst_api.h
SOURCES = tst_api.cpp

isEmpty(QBS_RELATIVE_PLUGINS_PATH):QBS_RELATIVE_PLUGINS_PATH=../$${QBS_LIBRARY_DIRNAME}
isEmpty(QBS_RELATIVE_SEARCH_PATH):QBS_RELATIVE_SEARCH_PATH=..
DEFINES += QBS_RELATIVE_PLUGINS_PATH=\\\"$${QBS_RELATIVE_PLUGINS_PATH}\\\"
DEFINES += QBS_RELATIVE_SEARCH_PATH=\\\"$${QBS_RELATIVE_SEARCH_PATH}\\\"
qbs_enable_project_file_updates:DEFINES += QBS_ENABLE_PROJECT_FILE_UPDATES

include(../auto.pri)

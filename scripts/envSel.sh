#!/bin/bash

SCRIPT_NAME=/tmp/script.$$

EnvSel select --output ${SCRIPT_NAME}

RC=$?

echo Returned ${RC}

if [ ${RC} -eq 0 ]; then

    cat ${SCRIPT_NAME}
    
    . ${SCRIPT_NAME}

    bash --rcfile ${SCRIPT_NAME} -i
    
    rm ${SCRIPT_NAME}
    
fi

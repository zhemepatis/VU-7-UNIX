#ifndef PROCESS_STATE_H
    #define PROCESS_STATE_H

    typedef enum
    {
        TO_BE_STARTED,
        RUNNING,
        STOPPED,
        DONE
    } ProcessState;

#endif
#ifndef gcode_H
#define gcode_H


/*
    G-code analyzer
*/
void AnalyzeCommand(uint8_t *buffer);

void AnalyzeCommandNext(uint8_t *buffer);

void AnalyzeCommandCurrent(uint8_t *buffer);


#endif

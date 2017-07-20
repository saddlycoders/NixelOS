/*
  NixelOS Kernel
  
  module name: logs.h
  
  (C) DiamondSoft (R) NixelOS 2017 - 2018 y.
  
*/
#ifndef LOGS_H
#define LOGS_H

#define LOG_LIMIT 5000
int lognum=0;
const char *logs[LOG_LIMIT];

void write_log(const char *def);

#endif
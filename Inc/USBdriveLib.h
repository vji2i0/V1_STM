#ifndef USBdriveLib
#define USBdriveLib

#include "fatfs.h"
#include "usb_host.h"

#define MAX_STRING_LENGTH 10
#define MAX_PATH_LENGTH 1000


typedef struct node_this
{
  char name[16]; // the name
  FILINFO fno; // file info. FILINFO : see more in /Middlewares/.../ff.h
  struct node_this * nextNode; // pointer to the next node
  struct node_this * previousNode; // pointer to the previous node
} node;




void ErrorCase(void);

void FileReadWrite(void);

void ReadFileByString(void);

void RootContentShort(void);

void RootContent(void);

void RootContentLinkedList(void);

void GoToTheFirstNode(void);

void GoToTheLastNode(void);

void ClearNodes(void);

void ShowRootContentLinkedList(void);

void FoulderContentLinkedList(void);

int FindSlash(char * string);

int FindNULL(char * string);

int FindDot(char * string);

_Bool IfGcode(char * string);

void ReadFile(void);

void OpenFolder(void);

void ShowNode(void);

void OKfunction(void);

void BACKfunction(void);

void UPfunction(void);

void DOWNfunction(void);

#endif

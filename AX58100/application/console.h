/*
 ******************************************************************************
 *     Copyright (c) 2011	ASIX Electronic Corporation      All rights reserved.
 *
 *     This is unpublished proprietary source code of ASIX Electronic Corporation
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ******************************************************************************
 */
#ifndef __CONSOLE_H__
#define __CONSOLE_H__

/* INCLUDE FILE DECLARATIONS */

/* NAMING CONSTANT DECLARATIONS */
#define CLI_AUTHEN_ENABLE 0
#define CLI_CMD_HISTORY_ENABLE 1
#define CLI_MAX_CMD_HISTORY_NUM	10

#define CLI_MAX_MESSAGE_LEN 512//128
#define CLI_MAX_COMMAND_LEN 512//128
#define CLI_MAX_CMD_LEN 24
#define CLI_MAX_USERNAME_LEN 16
#define CLI_MAX_PASSWD_LEN 16
#define CLI_MAX_PROMPT_LEN 16
#define CLI_MAX_CMD_BUF_LEN 100

enum LLID_Ind 
{
    LL_UART,
    LL_TELNET,
    LL_MAX
};

enum _CONSOLE_STATE_IND {
    CLI_STATE_BLOCK=0,
    CLI_STATE_LOGIN,
    CLI_STATE_PASSWD,
    CLI_STATE_COMMAND,
    CLI_STATE_COMMAND_WAIT,	
    CLI_STATE_PASSWD_CHANGE1,
    CLI_STATE_PASSWD_CHANGE2,
    CLI_STATE_PASSWD_CHANGE3,
    CLI_STATE_MAX
};

/* TYPE DECLARATIONS */
#if (CLI_CMD_HISTORY_ENABLE)
typedef struct
{
	unsigned char AddIndex;
	unsigned char GetIndex;
	char Buf[CLI_MAX_CMD_HISTORY_NUM][CLI_MAX_COMMAND_LEN];
} CONSOLE_CmdHistory;
#endif

 // Add for linked list algorithm //
struct _CLILINK
{
	struct _CLILINK *pPre;
	struct _CLILINK *pNext;
	unsigned short WaitTime;
	unsigned short ReplyLen;
	unsigned char Buf[CLI_MAX_CMD_BUF_LEN];
};
typedef struct _CLILINK tsCLILINK;

typedef struct
{
    unsigned char (*PutChar)(unsigned char c); /* write one character */
    char (*GetChar)(void);   /* read one character */  
    unsigned char Privilege;
    unsigned char State;
    unsigned char PromptEnable;
    unsigned char LowLayerId;
    unsigned short BufIndex;
    unsigned short CursorPosition;	
    unsigned short Argc;
    char **Argv;
    char CmdBuf[CLI_MAX_COMMAND_LEN];
    char UserName[CLI_MAX_USERNAME_LEN];
    char Passwd[CLI_MAX_PASSWD_LEN];
    char PasswdNew[CLI_MAX_PASSWD_LEN];
    char PromptStr[CLI_MAX_PROMPT_LEN];
	unsigned char CmdId;
	tsCLILINK Cmd; // Add for linked list algorithm //
#if (CLI_CMD_HISTORY_ENABLE)
    CONSOLE_CmdHistory CmdHistory;
#endif
	void *pCmdTable;
	unsigned short CmdTableSize;	
	unsigned short Timer;		
} CONSOLE_Inst;

typedef int (*CmdPtr)(CONSOLE_Inst *pInst, int argc, char **argv);
typedef int (*HelpPtr)(CONSOLE_Inst *pInst);

typedef struct
{
    char Cmd[CLI_MAX_CMD_LEN];
    CmdPtr CmdFunc;
    HelpPtr Help;
    unsigned char Level;
} CONSOLE_CmdEntry;

typedef struct
{
    char Name[CLI_MAX_USERNAME_LEN];
    char Passwd[CLI_MAX_PASSWD_LEN];
    unsigned char Level;
} CONSOLE_Account;

/* GLOBAL VARIABLES */

/* EXPORTED SUBPROGRAM SPECIFICATIONS */ 
void CONSOLE_Init(void);
void CONSOLE_Task(void);
short CONSOLE_PutMessage(CONSOLE_Inst *pInst, char *fmt, ...);
short CONSOLE_ChangeUsername(CONSOLE_Inst *pInst, unsigned char *username);
#if (INCLUDE_TELNET_SERVER)
CONSOLE_Inst *CONSOLE_GetInstance(unsigned char id);
#endif
short CONSOLE_TimeTick(void);

#endif /* __CONSOLE_H__ */

/* End of console.h */

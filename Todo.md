## Lexer
## Parser
redirect file something --> io
case 1:   echo OK > a
case 2:   > a echo OK 
- cat Makefile > a
COMPLETE_COMMAND
  SIMPLE_COMMAND: ["cat", "Makefile"]
    IO_REDIRECT
      REDIR_OUT: "a" , 0
- > a cat Makefile 
COMPLETE_COMMAND
  IO_REDIRECT
    REDIR_OUT: "a" , 0
The simple example of that you need to  have a simple cmd node before any any any any redir node
wc > a "ls -l"
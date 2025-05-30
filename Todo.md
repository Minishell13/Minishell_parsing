## Lexer
some|'some
## Parser

> ls |< aymane (ls)
syntax error: near unexpected token `ls'
> ls |< (ls)
syntax error near unexpected token `newline'> 
> ls |< (ls)
malloc(): unaligned tcache chunk detected
Aborted (core dumped)


> ls|cat"<a>b"
COMPLETE_COMMAND
  PIPE
    SIMPLE_COMMAND: [ ls ]
    SIMPLE_COMMAND: [ cat" ]
      IO_REDIRECT
        REDIR_IN: "a" , 0
        REDIR_OUT: "b"" , 0

        // else if (line[i] == '"')
        // {
        //     // read until you found close quote
        //     start = i;
        //     i++;
        //     while (line[i])
        //     {
        //         if (line[i] == '"')
        //         {
        //             i++;
        //             break;
        //         }
        //         i++;
        //     }
        //     if (line[i - 1] == '\n')
        //         line[i - 1] = '\0';
        //     word = ft_substr(line, start, i - start);
        //     if (!word)
        //         return (NULL);
        //     token_add_back(&head, create_token(word));
        //     free(word);
        // }
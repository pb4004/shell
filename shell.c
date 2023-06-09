#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "parser.h"
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h>
#include <fnmatch.h>

typedef struct _Node {
    char* word;
    struct _Node* next; 
} N;

N* head;
N* tail;
int size;
char* HOME;
int batch;

void execute(char** args, int argcount, N** start) {
    N* top = *start;
    // Print list
    N* ptr100 = head;
    while (ptr100) {
        ptr100 = ptr100->next;
    }
    if (argcount == 0 || strcmp(args[0], "") == 0) return;

    char* cmd = (char*) malloc(strlen(args[0])+1);
    strcpy(cmd, args[0]);
    struct stat file_stat;
    char *dest1 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest1, "/usr/local/sbin/");
    strncat(dest1, cmd, strlen(cmd));
    char *dest2 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest2, "/usr/local/bin/");
    strncat(dest2, cmd, strlen(cmd));
    char *dest3 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest3, "/usr/sbin/");
    strncat(dest3, cmd, strlen(cmd));
    char *dest4 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest4, "/usr/bin/");
    strncat(dest4, cmd, strlen(cmd));
    char *dest5 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest5, "/sbin/");
    strncat(dest5, cmd, strlen(cmd));
    char *dest6 = (char*)malloc(strlen(cmd) + 20);
    strcpy(dest6, "/bin/");
    strncat(dest6, cmd, strlen(cmd));
    
    if (strcmp(cmd, "cd") == 0) {
        int err = argcount == 1 ? chdir(HOME) : chdir(args[1]);
        if (err == -1) {
            perror("cd");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (strcmp(cmd, "exit") == 0) {
        N* free_ptr = top->next;
        while (free_ptr != NULL) {
            N* free_temp = free_ptr;
            free_ptr = free_ptr->next;
            free(free_temp->word);
            free(free_temp);
        }
        free(head);
        for (int i = 0; i < argcount+1; i++) {
            free(args[i]);
        }
        wait(NULL);
        if (!batch)
            write(1, "mysh: exiting\n", 14);
        while(1) exit(0);
    } else if (strcmp(cmd, "pwd") == 0) {
        char buffer[1000];
        char* res = getcwd(buffer, sizeof(buffer));
        if (res) {
            wait(NULL);
            write(1, buffer, strlen(buffer));
            write(1, "\n", 1);
        } else {
            perror("pwd");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest1, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest1, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest2, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest2, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest3, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest3, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest4, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest4, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest5, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest5, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else if (stat(dest6, &file_stat) == 0) {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(dest6, args);
            perror(cmd);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    } else {
        int pid, wstatus;
        pid = fork();
        if (pid < 0) {
            perror("fork");
            if (!batch) {wait(NULL); write(1, "!", 1);}
        } else if (pid == 0) {
            execv(cmd, args);
            wait(NULL);
            write(1, cmd, strlen(cmd));
            write(1, ": command not found\n", 20);
            exit(1);
        } else {
            wait(&wstatus);
            if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) && !batch) {wait(NULL); write(1, "!", 1);}
        }
    }
    
    free(cmd);
    free(dest1);
    free(dest2);
    free(dest3);
    free(dest4);
    free(dest5);
    free(dest6);
}

int main(int argc, char** argv) {
    N* head = (N*) malloc(sizeof(N));
    head->next = NULL;
    tail = head;
    size = 0;
    HOME = getenv("HOME");

    char *new_word;
    int fd = STDIN_FILENO;
    batch = 0;
    if (argc > 1) {
        batch = 1;
        fd = open(argv[1], O_RDONLY);
        if (fd == -1) {
            perror("open");
            if (!batch) {wait(NULL); write(1, "!", 1);}
            exit(1);
        }
    }

    words_init(fd);
    if (!batch) {
        wait(NULL);
        write(1, "Welcome to my shell!\n", 21);
        write(1, "mysh> ", 6);
    }
    int allow_newline = 1;
    while ((new_word = words_next())) {   

        if (strcmp(new_word, "") == 0) {
            continue;
        }

        int wordlen = strlen(new_word);
        if (new_word[wordlen-1] == '<' || new_word[wordlen-1] == '>' || new_word[wordlen-1] == '|') {
            N* new_node = (N*) malloc(sizeof(N));
            new_node->next = NULL;
            tail->next = new_node;
            tail = tail->next;
            size++;
            new_node->word = (char*) malloc(sizeof(char) * (wordlen+1));
            strncpy(new_node->word, new_word, wordlen+1);
            if (wordlen >= 2) {
                new_node->word[wordlen-1] = '\0';
                N* new_node_2 = (N*) malloc(sizeof(N));
                new_node_2->next = NULL;
                tail->next = new_node_2;
                tail = tail->next;
                size++;
                new_node_2->word = (char*) malloc(sizeof(char) * (4));
                new_node_2->word[0] = new_word[wordlen - 1];
                new_node_2->word[1] = '\0';
            }
        } else if (new_word[wordlen-1] == '\n') {
            if (wordlen > 1) {
                N* new_node = (N*) malloc(sizeof(N));
                new_node->next = NULL;
                tail->next = new_node;
                
                tail = tail->next;
                size++;
                new_node->word = (char*) malloc(sizeof(char) * (wordlen+1));
                strncpy(new_node->word, new_word, wordlen+1);
                new_node->word[wordlen-1] = '\0';
            }
            
            // execute...
            if (size == 0) {
             if (allow_newline && !batch) {
                    wait(NULL);
                    write(1, "mysh> ", 6);
                }
                free(new_word);
                continue;
            }
            // HOME dir ~
            N* ptr70 = head->next;
            while (ptr70) {
                if (strlen(ptr70->word) >= 2 && ptr70->word[0] == '~' && ptr70->word[1] == '/') {

                    char* tempWord = (char*) malloc(strlen(ptr70->word)+1);
                    strcpy(tempWord, ptr70->word);
                    int i = 0; 
                    ptr70->word = (char*) realloc(ptr70->word, strlen(HOME) + strlen(tempWord) + 1);
                    strcpy(ptr70->word, HOME);
                    i += 1;
                    strcat(ptr70->word, tempWord+1);
                    i += 1;
                    free(tempWord);
                } else if (strlen(ptr70->word) == 1 && ptr70->word[0] == '~') {
                    int j = 0; 
                    ptr70->word = (char*) realloc(ptr70->word, strlen(HOME) + strlen(ptr70->word) + 1);
                    strcpy(ptr70->word, HOME);
                    j += 1;
                } 
                ptr70 = ptr70->next;
            }

            N* ptr30 = head;
            while (ptr30->next) {
                int wildcard = 0;
                int backslash = 0;
                for(int i = 0; i < strlen(ptr30->next->word); i += 1) {
                    if (ptr30->next->word[i] == '/') {
                        backslash = 1;
                    } else if (ptr30->next->word[i] == '*') {
                        wildcard = 1;
                    }
                   
                }
                if (!wildcard) {
                    ptr30 = ptr30->next;
                    continue;
                }
                
                if (!backslash) {

                    DIR *dir;
                    struct dirent *entry;

                    dir = opendir(".");
                    if (dir == NULL) {
                        perror("opendir");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    
                    int matched = 0;
                    while ((entry = readdir(dir)) != NULL) {
                        if (entry->d_name[0] != '.' && fnmatch(ptr30->next->word, entry->d_name, 0) == 0) {
                            N* wild_match = (N*) malloc(sizeof(N));
                            wild_match->word = (char*) malloc(strlen(entry->d_name) + 1);
                            strcpy(wild_match->word, entry->d_name);
                            wild_match->next = ptr30->next->next;
                            ptr30->next->next = wild_match;
                            matched = 1;
                            size++;
                        }
                    }

                    if (matched) {
                        N* temp30 = ptr30->next;
                        ptr30->next = ptr30->next->next;
                        free(temp30->word);
                        free(temp30);
                        size--;
                    }
                    
                    closedir(dir);
                    
                } else {
                    char originalDir[1000];
                    getcwd(originalDir, sizeof(originalDir));

                    char *dirPath = (char *) (malloc(strlen(ptr30->next->word) + 1));
                    strcpy(dirPath, ptr30->next->word);
                    char * copyDirPath = (char *) (malloc(strlen(ptr30->next->word) + 1));
                    strcpy(copyDirPath, ptr30->next->word);

                    int index = 0;
                    int matched = 0;
                    char* token;
                    
                    // FIRST TOKEN
                    token = strtok(dirPath, "/");

                    int wildcard = 0;
                    for (int i = 0; i < strlen(token); i += 1) {
                        if (token[i] == '*') {
                            wildcard = 1;
                            break;
                        }
                    }

                    DIR *dir;
                    struct dirent *entry;
                    dir = opendir(".");
                    index += strlen(token)+1;

                    if (wildcard) {
                        while ((entry = readdir(dir)) != NULL) {
                            if (entry->d_name[0] != '.' && fnmatch(token, entry->d_name, 0) == 0) {
                                char* fullPath = (char*)(malloc(strlen(copyDirPath)+50));
                                strcpy(fullPath, entry->d_name);
                                char* restPath = copyDirPath + index;
                                strcat(fullPath, "/");
                                strcat(fullPath, restPath);
                                
                                struct stat file_stat;

                                if (stat(fullPath, &file_stat) == 0) {
                                     N* wild_match = (N*) malloc(sizeof(N));
                                    wild_match->word = (char*) malloc(strlen(copyDirPath)+50);
                                    strcpy(wild_match->word, fullPath);
                                    wild_match->next = ptr30->next->next;
                                    ptr30->next->next = wild_match;
                                    matched = 1;
                                    size++;
                                } 

                                free(fullPath);
                            }

                        }
                        if (matched) {
                            N* temp30 = ptr30->next;
                            ptr30->next = ptr30->next->next;
                            free(temp30->word);
                            free(temp30);
                            size--;
                        }
                    } else {
                        chdir(token);
                    }
                    char* tempPath = (char*) (calloc(strlen(copyDirPath)+50, 1));
                    while (token != NULL) {
                        token = strtok(NULL, "/");
                        if (token == NULL) {
                            break;
                        }

                        int wildcard = 0;
                        for (int i = 0; i < strlen(token); i += 1) {
                            if (token[i] == '*') {
                                wildcard = 1;
                                break;
                            }
                        }
                        DIR *dir;
                        struct dirent *entry;
                        dir = opendir(".");
                        if (wildcard) {
                            strncpy(tempPath, copyDirPath, index);
                        }
                        index += 1 + strlen(token);
                        if (wildcard) {
                            while ((entry = readdir(dir)) != NULL) {
                            
                                if (entry->d_name[0] != '.' && fnmatch(token, entry->d_name, 0) == 0) {
                                    char* fullPath = (char*)(malloc(strlen(copyDirPath)+50));
                                    strcpy(fullPath, entry->d_name);
                                    
                                    char* restPath = copyDirPath + index;
                                    
                                    if (index < strlen(copyDirPath)) {
                                        strcat(fullPath, "/");
                                        strcat(fullPath, restPath);
                                    }
                                    
                                    struct stat file_stat;

                                    if (stat(fullPath, &file_stat) == 0) {
                                        N* wild_match = (N*) malloc(sizeof(N));
                                        wild_match->word = (char*) malloc(strlen(tempPath) + strlen(fullPath) + 1);
                                        strcpy(wild_match->word, tempPath);
                                        strcat(wild_match->word, fullPath);
                                        wild_match->next = ptr30->next->next;
                                        ptr30->next->next = wild_match;
                                        matched = 1;
                                        size++;
                                    } 

                                    free(fullPath);
                                }
                            }
                            if (matched) {
                                N* temp30 = ptr30->next;
                                ptr30->next = ptr30->next->next;
                                free(temp30->word);
                                free(temp30);
                                size--;
                            }
                        } else {
                            chdir(token);
                        }
                        closedir(dir);
                    }
                    closedir(dir);
                    free(tempPath);
                    free(dirPath);
                    free(copyDirPath);
                    chdir(originalDir);
                }
                
                ptr30 = ptr30->next;
            }

                int totalCount = 0;
                // Construct args array
                int pipe2 = 0;
                int argcount = 0;
                int argcount2 = 0;
                N* ptr40 = head->next;
                int inCount = 0;
                int outCount = 0;
                while (ptr40) {
                    if (strcmp(ptr40->word, "<") == 0 || strcmp(ptr40->word, ">") == 0) {
                        if (strcmp(ptr40->word, "<") == 0) inCount++;
                        else outCount++;
                        totalCount += 1;

                        if (!pipe2) {
                            totalCount -= 1;
                            argcount--;
                        } else {
                            totalCount -= 1;
                            argcount2--;
                        }
                    } else if (strcmp(ptr40->word, "|") == 0) {
                        pipe2 = 1;
                        totalCount += 1;
                    } else {
                        if (!pipe2) {
                            totalCount += 1;
                            argcount++;
                        } else {
                            totalCount += 1;
                            argcount2++;
                        }
                    }
                    ptr40 = ptr40->next;
                }
                if (totalCount == inCount + outCount + argcount + argcount2) {
                }

                if (inCount > 1 || outCount > 1) {
                    totalCount = 0; 
                    wait(NULL);
                    write(1, "Too many outputs specified.\n", 28);
                    write(1, "!", 1);
                    N* free_ptr = head->next;
                    while (free_ptr != NULL) {
                        totalCount += 1;
                        N* free_temp = free_ptr;
                        free_ptr = free_ptr->next;
                        free(free_temp->word);
                        free(free_temp);
                    }
                    totalCount = 0;
                    size = 0;
                    tail = head;
                    if (allow_newline && !batch) {
                        wait(NULL);
                        write(1, "mysh> ", 6);
                    }
                    free(new_word);
                    continue;
                }
                totalCount = 0;
                char* args[argcount + 1];
                char* args2[argcount2 + 1];

                N* newDummy = (N*) (malloc(sizeof(N)));
                free(newDummy); 

                N* ptr1 = head->next;
                int i = 0;
                char* input_redirection;
                int foundInput = 0;
                char* output_redirection;
                int foundOutput = 0;
                int j = 0;
                int fillarg2 = 0;
                while (ptr1) {
                    if (strcmp(ptr1->word, "<") == 0) {
                        if (foundInput) free(input_redirection);
                        input_redirection = (char*) malloc(strlen(ptr1->next->word)+1);
                        foundInput = 1;
                        strcpy(input_redirection, ptr1->next->word);
                        ptr1 = ptr1->next;
                    } else if (strcmp(ptr1->word, ">") == 0) {
                        if (foundOutput) free(output_redirection);
                        output_redirection = (char*) malloc(strlen(ptr1->next->word)+1);
                        foundOutput = 1;
                        strcpy(output_redirection, ptr1->next->word);
                        ptr1 = ptr1->next;
                    } else if (strcmp(ptr1->word, "|") == 0) {
                        fillarg2 = 1;
                    } else {
                        if (!fillarg2){
                            args[i] = (char *) (malloc(strlen(ptr1->word) + 1));
                            strcpy(args[i], ptr1->word);
                            i += 1;
                        } else {
                            args2[j] = (char *) (malloc(strlen(ptr1->word) + 1));
                            strcpy(args2[j], ptr1->word);
                            j += 1;
                        }
                    }
                    ptr1 = ptr1->next;
                }
                args[argcount] = NULL;
                args2[argcount2] = NULL;
                
                int originalSTDIN = dup(STDIN_FILENO);
                if (foundInput) {
                    int pid;
                    pid = fork();
                    if (pid < 0) {
                        perror("fork");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                    } else if (pid == 0) {
                        int fd = open(input_redirection, O_RDONLY);
                        if (fd == -1) {
                            perror("open");
                            if (!batch) {wait(NULL); write(1, "!", 1);}
                            exit(1);
                        } else {
                            exit(0);
                        }

                        if (dup2(fd, STDIN_FILENO) == -1) {
                            perror("dup2");
                            if (!batch) {wait(NULL); write(1, "!", 1);}
                            exit(1);
                        }
                        close(fd);
                    } else {
                        wait(NULL);
                    }
                }
                if (foundInput) {
                    int getout = open(input_redirection, O_RDONLY);
                    if (getout == -1) {
                        N* free_ptr = head->next;
                        while (free_ptr != NULL) {
                            N* free_temp = free_ptr;
                            free_ptr = free_ptr->next;
                            free(free_temp->word);
                            free(free_temp);
                        }
                        size = 0;
                        tail = head;
                        if (allow_newline && !batch) {
                            wait(NULL);
                            write(1, "mysh> ", 6);
                        }
                        free(new_word);
                        dup2(originalSTDIN, STDIN_FILENO);
                        close(originalSTDIN);
                        free(input_redirection);
                        if (foundOutput)
                            free(output_redirection);
                        for (int i = 0; i <= argcount; i++) free(args[i]);
                        if (pipe2) {
                            for (int i = 0; i <= argcount2; i++) free(args2[i]);
                        }
                        continue;
                    } else {
                        close(getout);
                    }
                }
                int inputFound1 = 0;
                if (foundInput) {
                    int fd = open(input_redirection, O_RDONLY);
                     if (fd == -1) {
                        inputFound1 += 1;
                        perror("open");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    if (dup2(fd, STDIN_FILENO) == -1) {
                        inputFound1 -= 1;
                        perror("dup2");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    close(fd);

                    free(input_redirection);
                }
                int outputFound1 = 0;
                int originalSTDOUT = dup(STDOUT_FILENO);
                if (foundOutput) {
                    int pid;
                    pid = fork();
                    if (pid < 0) {
                        outputFound1 += 1;
                        perror("fork");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                    } else if (pid == 0) {
                        outputFound1 -= 1;
                        int fd = open(output_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0640);
                        if (fd == -1) {
                            perror("open");
                            if (!batch) {wait(NULL); write(1, "!", 1);}
                            exit(1);
                        }
                        if (dup2(fd, STDOUT_FILENO) == -1) {
                            perror("dup2");
                            if (!batch) {wait(NULL); write(1, "!", 1);}
                            exit(1);
                        }
                        close(fd);
                        exit(1);
                    } else {
                        wait(NULL);
                    }
                }
                int outputFound2 = 0;
                if (foundOutput) {
                    int fd = open(output_redirection, O_WRONLY | O_CREAT | O_TRUNC, 0640);
                    if (fd == -1) {
                        outputFound2 += 1;
                        perror("open");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    if (dup2(fd, STDOUT_FILENO) == -1) {
                        outputFound2 -= 1;
                        perror("dup2");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    close(fd);
                    free(output_redirection);
                }


                if (!pipe2) {
                    execute(args, argcount, &head);
                } else if (strcmp(args[0], "exit") == 0) {
                    execute(args2, argcount2, &head);
                    execute(args, argcount, &head);
                }
                else {
                    int fd[2];
                    int pid;
                   
                    if (pipe(fd) == -1) {
                        perror("pipe");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    }
                    pid = fork();
                    if (pid == -1) {
                        perror("fork");
                        if (!batch) {wait(NULL); write(1, "!", 1);}
                        exit(1);
                    } else if (pid == 0) {
                        close(fd[0]); 
                        dup2(fd[1], STDOUT_FILENO);
                        execute(args, argcount, &head);
                        allow_newline = 0;
                        close(fd[1]);
                        exit(0); // 
                    } else {
                        close(fd[1]); 
                        dup2(fd[0], STDIN_FILENO);
                        execute(args2, argcount2, &head);
                        allow_newline = 1;
                        close(fd[0]);
                    }

                }
                dup2(originalSTDOUT, STDOUT_FILENO);
                close(originalSTDOUT);
                dup2(originalSTDIN, STDIN_FILENO);
                close(originalSTDIN);
                for (int i = 0; i < argcount+1; i++) {
                    free(args[i]);
                }
                if (pipe2) {
                    for (int i = 0; i < argcount2+1; i++)
                        free(args2[i]);
                }
                
            // clear list
            N* free_ptr = head->next;
            while (free_ptr != NULL) {
                N* free_temp = free_ptr;
                free_ptr = free_ptr->next;
                free(free_temp->word);
                free(free_temp);
            }
            size = 0;
            tail = head;
            if (allow_newline && !batch) {
                wait(NULL);
                write(1, "mysh> ", 6);
            }
        } else {
            N* new_node = (N*) malloc(sizeof(N));
            new_node->next = NULL;
            tail->next = new_node;
            tail = tail->next;
            size++;
            new_node->word = (char*) malloc(sizeof(char) * (strlen(new_word) + 1));
            strcpy(new_node->word, new_word);
        }
        free(new_word);
    }
    free(head);
    return EXIT_SUCCESS;
}
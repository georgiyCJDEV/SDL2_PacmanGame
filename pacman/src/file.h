#pragma once

struct place
{
public:
    char name[50]{ "" };
    int score{ 0 };
};

struct list
{
public:
	struct place data;
	struct list* next{nullptr};
};

class File
{
public:
    ~File();
    struct list* new_node(struct list*, struct place);
    struct place input_player(char* name[], int&, int);
    void write_file(struct list*);
    void sort(struct list*);
    int nodecount(struct list*);
    void clearlastpos(struct list*);
    struct list* read_file();
    void delete_list(struct list*&);
};

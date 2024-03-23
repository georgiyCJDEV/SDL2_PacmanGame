#include "file.h"
#include <stdio.h>
#include <string.h>

File::~File()
{
}

void File::sort(struct list* cur)
{
    if (cur->next != nullptr)
    {
        struct list* next = cur->next;
        struct list* temp = new list;
        while (cur)
        {
            if (next->data.score > cur->data.score)
            {
                temp->data = cur->data;
                cur->data = next->data;
                next->data = temp->data;

            }
            cur = next;
            if (cur->next != nullptr)
            {
                next = cur->next;
            }
            else
            {
                break;
            }
        }
        delete temp;
    }
}

void File::clearlastpos(struct list* cur)
{
    int count = 0;
    while (cur)
    {
        count += 1;
        if (count > 10)
        {
            cur = nullptr;
            break;
        }
        cur = cur->next;

    }
}

int File::nodecount(struct list* cur)
{
    int count = 0;

    while (cur)
    {
        count++;
        cur = cur->next;
    }

    return count;
}

struct list* File::new_node(struct list* begin, struct place player)
{
    struct list* temp = new list;
    temp->data = player;
    temp->next = begin;
    return temp;
}

struct place File::input_player(char* name[], int& score, int len)
{
    struct place player;
    strcpy_s(player.name, *name);
    player.name[len] = '\0';
    player.score = score;
    return player;
}

void File::write_file(struct list* begin)
{

    FILE* file = nullptr;

    fopen_s(&file, "leaderboard/leaderboard", "wb");

    while (begin)
    {
        if (file != nullptr && fwrite(&begin->data, sizeof(struct place), 1, file))
        {
            begin = begin->next;
        }
    }


    if (file != nullptr)
    {
        fclose(file);
    }

}

struct list* File::read_file()
{

    FILE* file = nullptr;
    struct place player;
    struct list* begin = nullptr;
    struct list* cur = nullptr;

    fopen_s(&file, "leaderboard/leaderboard", "r");

    if (file != nullptr && fread(&player, sizeof(player), 1, file))
    {
        begin = new_node(nullptr, player);
    }

    else
    {
        return nullptr;
    }

    cur = begin;

    while (fread(&player, sizeof(player), 1, file))
    {
        cur->next = new_node(nullptr, player);
        cur = cur->next;
    }

    fclose(file);

    return begin;

}

void File::delete_list(struct list*& begin)
{
    struct list* temp = begin;
    while (temp)
    {
        begin = temp->next;
        delete temp;
        temp = begin;
    }
}
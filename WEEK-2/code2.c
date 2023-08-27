#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASH_TABLE_SIZE 100
struct SymbolEntry
{
    char *name;
    int value;
    struct SymbolEntry *next;
};
struct SymbolTable
{
    struct SymbolEntry *hash_table[HASH_TABLE_SIZE];
};
unsigned int hash(const char *str)
{
    unsigned int hash = 0;
    while (*str)
    {
        hash = (hash << 5) + *str++;
    }
    return hash % HASH_TABLE_SIZE;
}
void insert(struct SymbolTable *table, const char *name, int value)
{
    unsigned int index = hash(name);
    struct SymbolEntry *entry = (struct SymbolEntry *)malloc(sizeof(struct SymbolEntry));
    if (!entry)
    {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }
    entry->name = strdup(name);
    entry->value = value;
    entry->next = table->hash_table[index];
    table->hash_table[index] = entry;
}
struct SymbolEntry *search(struct SymbolTable *table, const char *name)
{
    unsigned int index = hash(name);
    struct SymbolEntry *entry = table->hash_table[index];
    while (entry != NULL)
    {
        if (strcmp(entry->name, name) == 0)
        {
            return entry;
        }
        entry = entry->next;
    }
    return NULL;
}
int main()
{
    struct SymbolTable symbol_table;
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        symbol_table.hash_table[i] = NULL;
    }
    insert(&symbol_table, "x", 59);
    insert(&symbol_table, "y", 27);
    struct SymbolEntry *entry_x = search(&symbol_table, "x");
    if (entry_x)
    {
        printf("Symbol: %s, Value: %d\n", entry_x->name, entry_x->value);
    }
    else
    {
        printf("Symbol not found.\n");
    }
    for (int i = 0; i < HASH_TABLE_SIZE; i++)
    {
        struct SymbolEntry *entry = symbol_table.hash_table[i];
        while (entry)
        {
            struct SymbolEntry *next = entry->next;
            free(entry->name);
            free(entry);
            entry = next;
        }
    }
    return 0;

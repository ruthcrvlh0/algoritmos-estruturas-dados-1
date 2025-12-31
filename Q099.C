#ifndef SPELLBOOK_H
#define SPELLBOOK_H

typedef struct {
    int id;
    char name[50];
    int mana_cost;
} Spell;

typedef struct spell_node {
    Spell spell;
    struct spell_node *next;
} SpellNode;

typedef struct {
    SpellNode *head;
} Spellbook;


/**
 * @brief Aloca e inicializa um novo grimório vazio.
 * @return Ponteiro para a nova estrutura Spellbook.
 */
Spellbook* create_spellbook();

/**
 * @brief Adiciona um novo feitiço ao final do grimório.
 * @param book O grimório.
 * @param id ID único do feitiço.
 * @param name Nome do feitiço.
 * @param mana_cost Custo de mana.
 */
void add_spell(Spellbook* book, int id, const char* name, int mana_cost);

/**
 * @brief Percorre e exibe todos os feitiços no grimório.
 * @param book O grimório a ser exibido.
 */
void display_spellbook(Spellbook* book);

/**
 * @brief Libera toda a memória alocada para o grimório (nós e a própria estrutura Spellbook).
 * @param book O grimório a ser destruído.
 */
void destroy_spellbook(Spellbook* book);

#endif 
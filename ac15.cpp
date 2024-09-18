#include <iostream>
#include <string>
#include <vector>

class DictionaryNode {
public:
    std::string word;
    std::string translation;
    int counter;

    DictionaryNode* left;
    DictionaryNode* right;

    DictionaryNode(const std::string& w, const std::string& t)
        : word(w), translation(t), counter(0), left(nullptr), right(nullptr) {}
};

class DictionaryTree {
private:
    DictionaryNode* root;

    void addNode(DictionaryNode*& node, const std::string& word, const std::string& translation) {
        if (!node) {
            node = new DictionaryNode(word, translation);
        } else if (word < node->word) {
            addNode(node->left, word, translation);
        } else if (word > node->word) {
            addNode(node->right, word, translation);
        } else {
            node->translation = translation;
        }
    }

    DictionaryNode* find(DictionaryNode* node, const std::string& word) {
        if (!node) return nullptr;
        if (word == node->word) {
            node->counter++;
            return node;
        }
        if (word < node->word) {
            return find(node->left, word);
        }
        return find(node->right, word);
    }

    void inOrder(DictionaryNode* node, std::vector<DictionaryNode*>& words) const {
        if (node) {
            inOrder(node->left, words);
            words.push_back(node);
            inOrder(node->right, words);
        }
    }

    void clear(DictionaryNode* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    DictionaryTree() : root(nullptr) {}

    ~DictionaryTree() {
        clear(root);
    }

    void add(const std::string& word, const std::string& translation) {
        addNode(root, word, translation);
    }

    void displayWord(const std::string& word) {
        DictionaryNode* node = find(root, word);
        if (node) {
            std::cout << "Word: " << word << ", Translation: " << node->translation << ", Count: " << node->counter << std::endl;
        } else {
            std::cout << "Word not found." << std::endl;
        }
    }

    void getTopWords(bool popular = true) {
        std::vector<DictionaryNode*> words;
        inOrder(root, words);

        sort(words.begin(), words.end(), [popular](DictionaryNode* a, DictionaryNode* b) {
            return popular ? a->counter > b->counter : a->counter < b->counter;
        });

        std::cout << (popular ? "Top-3 popular words:" : "Top-3 unpopular words:") << std::endl;
        for (int i = 0; i < 3 && i < words.size(); ++i) {
            std::cout << words[i]->word << ": " << words[i]->counter << std::endl;
        }
    }
};

int main() {
    DictionaryTree dict;

    dict.add("hello", "привіт");
    dict.add("world", "світ");
    dict.add("computer", "комп'ютер");
    dict.add("book", "книга");
    dict.add("tree", "дерево");

    dict.displayWord("world");
    dict.displayWord("hello");

    dict.getTopWords(true);  // Popular
    dict.getTopWords(false); // Unpopular

    return 0;
}

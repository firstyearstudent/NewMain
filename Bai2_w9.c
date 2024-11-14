#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_LENGTH 50
#define MAX_SENTENCE_LENGTH 500

typedef struct WordNode {
    char word[MAX_WORD_LENGTH];
    int frequency;
    struct WordNode* next;
} WordNode;

// Hàm sao chép chuỗi
void myStrCpy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0' && i < MAX_WORD_LENGTH - 1) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}

// Hàm so sánh chuỗi
int myStrCmp(const char* str1, const char* str2) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0') return 0;
        i++;
    }
    return str1[i] - str2[i];
}

// Hàm thêm từ vào danh sách hoặc tăng tần suất nếu từ đã tồn tại
void addWord(WordNode** head, const char* word) {
    WordNode* current = *head;
    while (current != NULL) {
        if (myStrCmp(current->word, word) == 0) {
            current->frequency++;
            return;
        }
        current = current->next;
    }

    WordNode* newWord = (WordNode*)malloc(sizeof(WordNode));
    myStrCpy(newWord->word, word);
    newWord->frequency = 1;
    newWord->next = *head;
    *head = newWord;
}

// Hàm tìm từ xuất hiện nhiều nhất
WordNode* findMostFrequentWord(WordNode* head) {
    WordNode* mostFrequent = head;
    while (head != NULL) {
        if (head->frequency > mostFrequent->frequency) {
            mostFrequent = head;
        }
        head = head->next;
    }
    return mostFrequent;
}

// Hàm loại bỏ từ lặp lại liên tiếp
void removeRedundantRepetitiveWord(WordNode** head) {
    WordNode* current = *head;
    while (current != NULL && current->next != NULL) {
        if (myStrCmp(current->word, current->next->word) == 0) {
            WordNode* redundant = current->next;
            current->next = redundant->next;
            free(redundant);
        } else {
            current = current->next;
        }
    }
}

// Hàm đếm số từ vựng
int countUniqueWords(WordNode* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

// Hàm in danh sách từ
void printWords(WordNode* head) {
    while (head != NULL) {
        printf("Word: %s, Frequency: %d\n", head->word, head->frequency);
        head = head->next;
    }
}

// Hàm tách từ từ câu nhập vào
void splitSentence(WordNode** head, char* sentence) {
    int i = 0, j = 0;
    char word[MAX_WORD_LENGTH];

    while (sentence[i] != '\0') {
        if (sentence[i] != ' ' && sentence[i] != '\n') {
            if (j < MAX_WORD_LENGTH - 1) {
                word[j++] = sentence[i];
            }
        } else {
            if (j > 0) {
                word[j] = '\0';
                addWord(head, word);
                j = 0;
            }
        }
        i++;
    }

    if (j > 0) {
        word[j] = '\0';
        addWord(head, word);
    }
}

// Hàm chính
int main() {
    WordNode* head = NULL;
    char sentence[MAX_SENTENCE_LENGTH];

    // Yêu cầu người dùng nhập một câu
    printf("Nhap mot cau: ");
    fgets(sentence, MAX_SENTENCE_LENGTH, stdin);

    // Tách câu thành các từ và thêm vào danh sách liên kết
    splitSentence(&head, sentence);

    printf("Danh sach tu ban dau:\n");
    printWords(head);

    // Tìm từ xuất hiện nhiều nhất
    WordNode* mostFrequent = findMostFrequentWord(head);
    if (mostFrequent) {
        printf("Tu lay: %s, Tan suat: %d\n", mostFrequent->word, mostFrequent->frequency);
    }

    // Loại bỏ từ lặp lại
    removeRedundantRepetitiveWord(&head);

    printf("Danh sach tu sau khi loai bo tu lap lai:\n");
    printWords(head);

    // Đếm số từ vựng
    printf("So tu vung: %d\n", countUniqueWords(head));

    // Giải phóng bộ nhớ
    while (head != NULL) {
        WordNode* temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}

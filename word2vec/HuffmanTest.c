/**
*  from google word2vec c语言 implement
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LENGTH 40

long long vocab_size;
long long vocab_max_size=100;

struct vocab_word
{
  long long cn;
  int *point;
  char *word, *code, codelen;
};

struct vocab_word *vocab;

// Create binary Huffman tree using the word counts
// Frequent words will have short uniqe binary codes
void CreateBinaryTree()
{
  long long a, b, i, min1i, min2i, pos1, pos2, point[MAX_CODE_LENGTH];
  char code[MAX_CODE_LENGTH];
  long long *count = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
  long long *binary = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
  long long *parent_node = (long long *)calloc(vocab_size * 2 + 1, sizeof(long long));
  for (a = 0; a < vocab_size; a++)
    count[a] = vocab[a].cn;
  for (a = vocab_size; a < vocab_size * 2; a++)
    count[a] = 1e15;
  pos1 = vocab_size - 1;
  pos2 = vocab_size;
  // Following algorithm constructs the Huffman tree by adding one node at a time
  for (a = 0; a < vocab_size - 1; a++)
  {
    // First, find two smallest nodes 'min1, min2'
    if (pos1 >= 0)
    {
      if (count[pos1] < count[pos2])
      {
        min1i = pos1;
        pos1--;
      }
      else
      {
        min1i = pos2;
        pos2++;
      }
    }
    else
    {
      min1i = pos2;
      pos2++;
    }
    if (pos1 >= 0)
    {
      if (count[pos1] < count[pos2])
      {
        min2i = pos1;
        pos1--;
      }
      else
      {
        min2i = pos2;
        pos2++;
      }
    }
    else
    {
      min2i = pos2;
      pos2++;
    }
    count[vocab_size + a] = count[min1i] + count[min2i];
    parent_node[min1i] = vocab_size + a;
    parent_node[min2i] = vocab_size + a;
    binary[min2i] = 1; //second smallest leaf node is 1
  }
  // Now assign binary code to each vocabulary word
  for (a = 0; a < vocab_size; a++)
  {
    b = a;
    i = 0; //i: the length of leaf node to root
    while (1)
    {
      code[i] = binary[b];
      point[i] = b; //point : point in path (path is leaf to root)
      i++;
      b = parent_node[b];
      if (b == vocab_size * 2 - 2)
        break; //all leaf node will pass root node
    }
    vocab[a].codelen = i;
    vocab[a].point[0] = vocab_size - 2;    //reverse, point[0] is root, in fact need add vocab_size, vocab_size-2 is offset by  2*vocab_size-2
    for (b = 0; b < i; b++)
    {
      vocab[a].code[i - b - 1] = code[b];            //but from vocab.code view ,up to down (root to leaf i->0)
      vocab[a].point[i - b] = point[b] - vocab_size; //point[i] maybe negative
    }
  }
  free(count);
  free(binary);
  free(parent_node);
}

void AddWordToVocab(char *word, int cn)
{
  unsigned int length = strlen(word) + 1;
  vocab[vocab_size].word = (char *)calloc(length, sizeof(char));
  strcpy(vocab[vocab_size].word, word);
  vocab[vocab_size].cn = cn;
  vocab_size++;
}

int main()
{

  vocab = (struct vocab_word *)calloc(vocab_max_size, sizeof(struct vocab_word));
  char *word = (char *)"</s>";
  AddWordToVocab(word, 0);
  AddWordToVocab((char *)"the", 100);
  AddWordToVocab((char *)"of",  98);
  AddWordToVocab((char *)"and", 95);
  AddWordToVocab((char *)"one", 80);
  AddWordToVocab((char *)"in", 67);

  vocab = (struct vocab_word *)realloc(vocab, (vocab_size + 1) * sizeof(struct vocab_word));
  // Allocate memory for the binary tree construction
  for (int a = 0; a < vocab_size; a++)
  {
    vocab[a].code = (char *)calloc(MAX_CODE_LENGTH, sizeof(char));
    vocab[a].point = (int *)calloc(MAX_CODE_LENGTH, sizeof(int));
  }
  CreateBinaryTree();
}
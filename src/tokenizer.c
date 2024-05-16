// POSIX Shell Tokenizer

#include "tokenizer.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/vector/vector.h"

// https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html

struct Token* newToken(int type, char* value) {
  struct Token* token = malloc(sizeof(struct Token));
  token->type = type;
  strncat(token->value, value, 99);
  return token;
}

// tokenize input
void tokenize(vector* tokenVector, char* input) {
  size_t len = strlen(input);

  // test token
  // vector_add(tokenVector, new_token(Word, "test"));

  // struct Token* firstToken = (struct Token*)vector_get(tokenVector, 0);

  char c = '\0';
  size_t tokenStart = 0;
  size_t tokenEnd = 0;
  size_t numTokens = 0;

  // Flags for tokenizing
  int inQuote = 0;
  int inDQuote = 0;
  int inEscape = 0;
  int inComment = 0;

  // ✅ If the end of input is recognized, the current token (if any) shall be delimited.

  // If the previous character was used as part of an operator and the current character is not quoted and can be used with the previous characters to form an operator, it shall be used as part of that (operator) token.

  // If the previous character was used as part of an operator and the current character cannot be used with the previous characters to form an operator, the operator containing the previous character shall be delimited.

  // If the current character is <backslash>, single-quote, or double-quote and it is not quoted, it shall affect quoting for subsequent characters up to the end of the quoted text. The rules for quoting are as described in Quoting . During token recognition no substitutions shall be actually performed, and the result token shall contain exactly the characters that appear in the input (except for <newline> joining), unmodified, including any embedded or enclosing quotes or substitution operators, between the <quotation-mark> and the end of the quoted text. The token shall not be delimited by the end of the quoted field.

  // If the current character is an unquoted '$' or '`', the shell shall identify the start of any candidates for parameter expansion (Parameter Expansion), command substitution (Command Substitution), or arithmetic expansion (Arithmetic Expansion) from their introductory unquoted character sequences: '$' or "${", "$(" or '`', and "$((", respectively. The shell shall read sufficient input to determine the end of the unit to be expanded (as explained in the cited sections). While processing the characters, if instances of expansions or quoting are found nested within the substitution, the shell shall recursively process them in the manner specified for the construct that is found. The characters found from the beginning of the substitution to its end, allowing for any recursion necessary to recognize embedded constructs, shall be included unmodified in the result token, including any embedded or enclosing substitution operators or quotes. The token shall not be delimited by the end of the substitution.

  // If the current character is not quoted and can be used as the first character of a new operator, the current token (if any) shall be delimited. The current character shall be used as the beginning of the next (operator) token.

  // If the current character is an unquoted <blank>, any token containing the previous character is delimited and the current character shall be discarded.

  // If the previous character was part of a word, the current character shall be appended to that word.

  // ✅ If the current character is a '#', it and all subsequent characters up to, but excluding, the next <newline> shall be discarded as a comment. The <newline> that ends the line is not considered part of the comment.

  // The current character is used as the start of a new word.

#define isOperator(c) (c == ';' || c == '&' || c == '|' || c == '<' || c == '>' || c == '(' || c == ')' || c == '{' || c == '}' || c == '!' || c == '=')
#define isWhitespace(c) (c == ' ' || c == '\t' || c == '\n' || c == '\r')
#define isQuote(c) (c == '\'' || c == '"')
#define isEscape(c) (c == '\\')
#define isComment(c) (c == '#')

  struct Token* token = newToken(Word, "");
#define addToken(t)               \
  vector_add(tokenVector, token); \
  token = newToken(t, "");

  for (size_t i = 0; i < len; i++) {
    c = input[i];

    if (c == '#') {
      inComment = 1;
      addToken(Comment);
    }

    if (inComment) {
      if (c == '\n') {
        inComment = 0;
        addToken(Newline);
      }
      token->value[0] = '\0';
      continue;
    }
  }
  if (token->value[0] != '\0') vector_add(tokenVector, token);

  // Capture last token
  // vector_add(&tokenVector, &currentToken);
}

char* prettyPrintTokens(vector* tokenVector) {
  int ansiColors[16] = {30, 31, 32, 33, 34, 35, 36, 37, 90, 91, 92, 93, 94, 95, 96, 97};
  char* prettyPrint = malloc(vector_reduce(tokenVector, 0, strlen) + tokenVector->total * 5);
  for (size_t i = 0; i < tokenVector->total; i++) {
    struct Token* token = (struct Token*)tokenVector->items[i];
    // printf("\e[%im%s\e[0m", ansiColors[token->type % 16], token->value);
    sprintf(prettyPrint, "%s\e[%im%s", prettyPrint, ansiColors[/* token->type */ i % 16], token->value);
  }
  return prettyPrint;
}
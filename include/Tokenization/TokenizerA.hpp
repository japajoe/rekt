#ifndef REKT_TOKENIZER_A_HPP
#define REKT_TOKENIZER_A_HPP

#include <iostream>
#include <vector>
#include <Token.hpp>

namespace REKT
{
    class TokenizerA
    {
    public:
        std::vector<Token<PrimitiveTokenType>> Parse(const std::string& source)
        {
            std::vector<Token<PrimitiveTokenType>> tokens;
            Token<PrimitiveTokenType> currentToken;

            currentToken.type = PrimitiveTokenType::WhiteSpace;
            currentToken.lineNumber = 1;

            for(char currentChar : source)
            {
                if(currentToken.type == PrimitiveTokenType::StringEscapeSequence)
                {
                    switch(currentChar)
                    {
                        case 'n':
                            AppendCharacter(currentToken, '\n');
                            break;
                        case 'r':
                            AppendCharacter(currentToken, '\r');
                            break;
                        case 't':
                            AppendCharacter(currentToken, '\t');
                            break;
                        case '\\':
                            AppendCharacter(currentToken, '\\');
                            break;
                        default:
                            std::cout << "Unknown escape sequence: \\" << currentChar << " on line " << currentToken.lineNumber;
                    }
                    currentToken.type = PrimitiveTokenType::StringLiteral;
                    continue;
                }

                else if(currentToken.type == PrimitiveTokenType::PotentialComment && currentChar != ';')
                {
                    currentToken.type = PrimitiveTokenType::Operator;
                    EndToken(currentToken, tokens);
                    continue;
                }

                switch(currentChar)
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                        if(currentToken.type == PrimitiveTokenType::WhiteSpace)
                        {
                            currentToken.type = PrimitiveTokenType::IntegerLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == PrimitiveTokenType::PotentialFloatingPoint)
                        {
                            currentToken.type = PrimitiveTokenType::FloatingPointLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;
                    
                    case '.':
                        if(currentToken.type == PrimitiveTokenType::WhiteSpace)
                        {
                            currentToken.type = PrimitiveTokenType::PotentialFloatingPoint;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == PrimitiveTokenType::IntegerLiteral)
                        {
                            currentToken.type = PrimitiveTokenType::FloatingPointLiteral;
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == PrimitiveTokenType::StringLiteral)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = PrimitiveTokenType::Operator;
                            AppendCharacter(currentToken, currentChar);
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '{':
                    case '}':
                    case '(':
                    case ')':
                    case '[':
                    case ']':
                    case '=':
                    case '-':
                    case '+':
                    case '*':
                    case '%':
                    case '&':
                    case '!':
                    case ',':
                    case ':':
                        if(currentToken.type != PrimitiveTokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = PrimitiveTokenType::Operator;
                            currentToken.text += currentChar;
                            EndToken(currentToken, tokens);
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;

                    case ' ':
                    case '\t':
                        if(currentToken.type == PrimitiveTokenType::StringLiteral || currentToken.type == PrimitiveTokenType::Comment)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '\r':
                    case '\n':
                        EndToken(currentToken, tokens);
                        ++currentToken.lineNumber;
                        break;

                    case '"':
                        if(currentToken.type != PrimitiveTokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = PrimitiveTokenType::StringLiteral;
                        }
                        else if(currentToken.type == PrimitiveTokenType::StringLiteral)
                        {
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case '\\':
                        if(currentToken.type == PrimitiveTokenType::StringLiteral)
                        {
                            currentToken.type = PrimitiveTokenType::StringEscapeSequence;
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = PrimitiveTokenType::Operator;
                            AppendCharacter(currentToken, currentChar);
                            EndToken(currentToken, tokens);
                        }
                        break;

                    case ';':
                        if(currentToken.type == PrimitiveTokenType::StringLiteral)
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        else if(currentToken.type == PrimitiveTokenType::PotentialComment)
                        {
                            currentToken.type = PrimitiveTokenType::Comment;
                            currentToken.text = "";
                        }
                        else
                        {
                            EndToken(currentToken, tokens);
                            currentToken.type = PrimitiveTokenType::PotentialComment;
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;

                    default:
                        if(currentToken.type == PrimitiveTokenType::WhiteSpace || currentToken.type == PrimitiveTokenType::IntegerLiteral || currentToken.type == PrimitiveTokenType::FloatingPointLiteral)
                        {
                            if(currentToken.type == PrimitiveTokenType::IntegerLiteral)
                            {
                                switch(currentChar)
                                {
                                    case 'x':
                                    case 'a':
                                    case 'A':
                                    case 'b':
                                    case 'B':
                                    case 'c':
                                    case 'C':
                                    case 'd':
                                    case 'D':
                                    case 'e':
                                    case 'E':
                                    case 'f':
                                    case 'F':
                                        currentToken.type = PrimitiveTokenType::IntegerLiteral;
                                        AppendCharacter(currentToken, currentChar);
                                        break;
                                    default:
                                        EndToken(currentToken, tokens);
                                        currentToken.type = PrimitiveTokenType::Identifier;
                                        AppendCharacter(currentToken, currentChar);
                                        break;
                                }

                            }
                            else
                            {
                                EndToken(currentToken, tokens);
                                currentToken.type = PrimitiveTokenType::Identifier;
                                AppendCharacter(currentToken, currentChar);
                            }
                        }
                        else
                        {
                            AppendCharacter(currentToken, currentChar);
                        }
                        break;
                }
            }
            
            EndToken(currentToken, tokens);

            return tokens;
        }

    private:
        void EndToken(Token<PrimitiveTokenType>& token, std::vector<Token<PrimitiveTokenType>>& tokens)
        {
            if(token.type == PrimitiveTokenType::Comment)
            {
                //Console.WriteLine("Ignoring comment: " + token.text);
            }
            else if(token.type != PrimitiveTokenType::WhiteSpace)
            {
                tokens.push_back(token);
            }
            if(token.type == PrimitiveTokenType::PotentialFloatingPoint)
            {
                if(token.text == ".")
                {
                    token.type = PrimitiveTokenType::Operator;
                }
                else
                {
                    token.type = PrimitiveTokenType::FloatingPointLiteral;
                }
            }


            token.type = PrimitiveTokenType::WhiteSpace;
            token.text = "";
        }

        void AppendCharacter(Token<PrimitiveTokenType>& token, char c)
        {
            token.text += c;
        }    
    };
}
#endif
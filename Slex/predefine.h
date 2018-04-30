#pragma once

#define DEBUG

#define SYMBOL              int         //表示任意符号
#define OPERATOR            int         //表示运算符号
#define TERMINAL            int         //表示终结符号
#define NODE_ID             int         //表示状态机结点ID

#define EPSILON             300         //空字符        \e
#define OPEN_PAREN          301         //左圆括号      (
#define CLOSE_PAREN         302         //右圆括号      )
#define KLEENE_CLOSURE      303         //克林闭包      *
#define CONCATENATION       304         //连接运算      \c
#define UNION               305         //或运算        |

#define OPEN_CURLY          400         //左花括号      {
#define CLOSE_CURLY         401         //右花括号      }
#define OPEN_BRACKET        402         //左方括号      [
#define CLOSE_BRACKET       403         //右方括号      ]
#define PERIOD              404         //句号          .
#define HYPHEN              405         //连字符        -
#define CARET               406         //补字符        ^
#define POSITIVE_CLOSURE    407         //正闭包        +
#define QUESTION            408         //问号          ?
#define QUOTATION           409         //引号          "
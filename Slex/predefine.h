#pragma once

#define YY_DEBUG

#define YY_SYMBOL              int         //表示任意符号
#define YY_OPERATOR            int         //表示运算符号
#define YY_TERMINAL            int         //表示终结符号
#define YY_NODE_ID             int         //表示状态机结点ID

#define YY_EPSILON             300         //空字符        \e
#define YY_OPEN_PAREN          301         //左圆括号      (
#define YY_CLOSE_PAREN         302         //右圆括号      )
#define YY_KLEENE_CLOSURE      303         //克林闭包      *
#define YY_CONCATENATION       304         //连接运算      \c
#define YY_UNION               305         //或运算        |

#define YY_OPEN_CURLY          400         //左花括号      {
#define YY_CLOSE_CURLY         401         //右花括号      }
#define YY_OPEN_BRACKET        402         //左方括号      [
#define YY_CLOSE_BRACKET       403         //右方括号      ]
#define YY_PERIOD              404         //句号          .
#define YY_HYPHEN              405         //连字符        -
#define YY_CARET               406         //补字符        ^
#define YY_POSITIVE_CLOSURE    407         //正闭包        +
#define YY_QUESTION            408         //问号          ?
#define YY_QUOTATION           409         //引号          "
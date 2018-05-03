#pragma once

#define YY_DEBUG

#define YY_SYMBOL              int         //��ʾ�������
#define YY_OPERATOR            int         //��ʾ�������
#define YY_TERMINAL            int         //��ʾ�ս����
#define YY_NODE_ID             int         //��ʾ״̬�����ID

#define YY_EPSILON             300         //���ַ�        \e
#define YY_OPEN_PAREN          301         //��Բ����      (
#define YY_CLOSE_PAREN         302         //��Բ����      )
#define YY_KLEENE_CLOSURE      303         //���ֱհ�      *
#define YY_CONCATENATION       304         //��������      \c
#define YY_UNION               305         //������        |

#define YY_OPEN_CURLY          400         //������      {
#define YY_CLOSE_CURLY         401         //�һ�����      }
#define YY_OPEN_BRACKET        402         //������      [
#define YY_CLOSE_BRACKET       403         //�ҷ�����      ]
#define YY_PERIOD              404         //���          .
#define YY_HYPHEN              405         //���ַ�        -
#define YY_CARET               406         //���ַ�        ^
#define YY_POSITIVE_CLOSURE    407         //���հ�        +
#define YY_QUESTION            408         //�ʺ�          ?
#define YY_QUOTATION           409         //����          "
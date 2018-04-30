#pragma once

#define DEBUG

#define SYMBOL              int         //��ʾ�������
#define OPERATOR            int         //��ʾ�������
#define TERMINAL            int         //��ʾ�ս����
#define NODE_ID             int         //��ʾ״̬�����ID

#define EPSILON             300         //���ַ�        \e
#define OPEN_PAREN          301         //��Բ����      (
#define CLOSE_PAREN         302         //��Բ����      )
#define KLEENE_CLOSURE      303         //���ֱհ�      *
#define CONCATENATION       304         //��������      \c
#define UNION               305         //������        |

#define OPEN_CURLY          400         //������      {
#define CLOSE_CURLY         401         //�һ�����      }
#define OPEN_BRACKET        402         //������      [
#define CLOSE_BRACKET       403         //�ҷ�����      ]
#define PERIOD              404         //���          .
#define HYPHEN              405         //���ַ�        -
#define CARET               406         //���ַ�        ^
#define POSITIVE_CLOSURE    407         //���հ�        +
#define QUESTION            408         //�ʺ�          ?
#define QUOTATION           409         //����          "
#include<stdio.h>

int main(void)
{
    int h_1, h_2, m_1, m_2;

    scanf("%d%d%d%d", &h_1, &m_1, &h_2, &m_2);

    if((m_2 - m_1) < 0) {
        ++h_2;
        m_2+=60;
    }

    printf("%d %d", h_2 - h_1, m_2 - m_1);

    return 0;
}

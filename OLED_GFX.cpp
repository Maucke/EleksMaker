#include "OLED_GFX.h"
#include "ASCII_Font.h"

#include "stdlib.h"


uint8_t Row, Column;
FONT_SIZE Font_Size;


#ifdef __cplusplus
extern "C" {
#endif

    OLED_GFX::OLED_GFX(void) {
        Row = 0;
        Column = 0;
        Font_Size = FONT_5X8;
    }

    void OLED_GFX::Set_FontSize(FONT_SIZE size) {
        Font_Size = size;
    }

    void OLED_GFX::print_String(uint8_t x, uint8_t y, const uint8_t* text, FONT_SIZE size) {

        Font_Size = size;

        if (Font_Size == FONT_5X8)
            Display_String_5x8(x, y, text);
        else if (Font_Size == FONT_8X16)
            Display_String_8x16(x, y, text);

    }

    void OLED_GFX::Display_String_8x16(uint8_t x, uint8_t y, const uint8_t* text) {

    }

    void OLED_GFX::Display_String_5x8(uint8_t x, uint8_t y, const uint8_t* text) {

    }

    void OLED_GFX::Set_TextCoordinate(uint8_t x, uint8_t y) {

        Column = x;
        Row = y;
    }

    void OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {
        // Update in subclasses if desired!
        if (x0 == x1) {
            if (y0 > y1) swapl(y0, y1);
            Draw_FastVLine(x0, y0, y1 - y0);
        }
        else if (y0 == y1) {
            if (x0 > x1)
                swapl(x0, x1);
            Draw_FastHLine(x0, y0, x1 - x0);
        }
        else
            Write_Line(x0, y0, x1, y1);
    }

    void OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
        // Update in subclasses if desired!
        if (x0 == x1) {
            if (y0 > y1) swapl(y0, y1);
            Draw_FastVLine(x0, y0, y1 - y0, color);
        }
        else if (y0 == y1) {
            if (x0 > x1)
                swapl(x0, x1);
            Draw_FastHLine(x0, y0, x1 - x0, color);
        }
        else
            Write_Line(x0, y0, x1, y1, color);
    }

    void  OLED_GFX::Draw_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8 with, uint16_t color)
    {
        int32   dx;						// 直线x轴差值变量
        int32   dy;          			// 直线y轴差值变量
        int16    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
        int16    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
        int32   dx_x2;					// dx*2值变量，用于加快运算速度
        int32   dy_x2;					// dy*2值变量，用于加快运算速度
        int32   di;						// 决策变量

        int32   wx, wy;					// 线宽变量
        int32   draw_a, draw_b;

        /* 参数过滤 */
        if (with == 0) return;
        if (with > 50) with = 50;

        dx = x1 - x0;						// 求取两点之间的差值
        dy = y1 - y0;

        wx = with / 2;
        wy = with - wx - 1;

        /* 判断增长方向，或是否为水平线、垂直线、点 */
        if (dx > 0)							// 判断x轴方向
        {
            dx_sym = 1;					// dx>0，设置dx_sym=1
        }
        else
        {
            if (dx < 0)
            {
                dx_sym = -1;				// dx<0，设置dx_sym=-1
            }
            else
            {  /* dx==0，画垂直线，或一点 */
                wx = x0 - wx;
                if (wx < 0) wx = 0;
                wy = x0 + wy;

                while (1)
                {
                    x0 = wx;

                    if (y0 > y1)
                        swapl(y0, y1);
                    Draw_FastVLine(x0, y0, y1 - y0, color);
                    if (wx >= wy) break;
                    wx++;
                }

                return;
            }
        }

        if (dy > 0)							// 判断y轴方向
        {
            dy_sym = 1;					// dy>0，设置dy_sym=1
        }
        else
        {
            if (dy < 0)
            {
                dy_sym = -1;				// dy<0，设置dy_sym=-1
            }
            else
            {  /* dy==0，画水平线，或一点 */
                wx = y0 - wx;
                if (wx < 0) wx = 0;
                wy = y0 + wy;

                while (1)
                {
                    y0 = wx;
                    if (x0 > x1)
                        swapl(x0, x1);
                    Draw_FastHLine(x0, y0, x1 - x0, color);
                    if (wx >= wy) break;
                    wx++;
                }
                return;
            }
        }

        /* 将dx、dy取绝对值 */
        dx = dx_sym * dx;
        dy = dy_sym * dy;

        /* 计算2倍的dx及dy值 */
        dx_x2 = dx * 2;
        dy_x2 = dy * 2;

        /* 使用Bresenham法进行画直线 */
        if (dx >= dy)						// 对于dx>=dy，则使用x轴为基准
        {
            di = dy_x2 - dx;
            while (x0 != x1)
            {  /* x轴向增长，则宽度在y方向，即画垂直线 */
                draw_a = y0 - wx;
                if (draw_a < 0) draw_a = 0;
                draw_b = y0 + wy;
                if (draw_a > draw_b)
                    swapl(draw_a, draw_b);
                Draw_FastVLine(x0, draw_a, draw_b - draw_a, color);

                x0 += dx_sym;
                if (di < 0)
                {
                    di += dy_x2;			// 计算出下一步的决策值
                }
                else
                {
                    di += dy_x2 - dx_x2;
                    y0 += dy_sym;
                }
            }
            draw_a = y0 - wx;
            if (draw_a < 0) draw_a = 0;
            draw_b = y0 + wy;
            if (draw_a > draw_b)
                swapl(draw_a, draw_b);
            Draw_FastVLine(x0, draw_a, draw_b - draw_a, color);
        }
        else								// 对于dx<dy，则使用y轴为基准
        {
            di = dx_x2 - dy;
            while (y0 != y1)
            {  /* y轴向增长，则宽度在x方向，即画水平线 */
                draw_a = x0 - wx;
                if (draw_a < 0) draw_a = 0;
                draw_b = x0 + wy;
                if (draw_a > draw_b)
                    swapl(draw_a, draw_b);
                Draw_FastHLine(draw_a, y0, draw_b - draw_a, color);

                y0 += dy_sym;
                if (di < 0)
                {
                    di += dx_x2;
                }
                else
                {
                    di += dx_x2 - dy_x2;
                    x0 += dx_sym;
                }
            }
            draw_a = x0 - wx;
            if (draw_a < 0) draw_a = 0;
            draw_b = x0 + wy;
            if (draw_a > draw_b)
                swapl(draw_a, draw_b);
            Draw_FastHLine(draw_a, y0, draw_b - draw_a, color);
        }

    }


    /****************************************************************************
    * 名称：GUI_LineS()
    * 功能：多个点之间的连续连线。从第一点连到第二点，再连到第三点...
    * 入口参数： points  多个点坐标数据的指针，数据排列为(x0,y0)、(x1,y1)、(x2,y2)...
    *           no      点数目，至少要大于1
    * 出口参数：无
    * 说明：操作失败原因是指定地址超出有效范围。
    ****************************************************************************/

    void  OLED_GFX::Draw_LineS(int16* points, uint8 no)
    {
        uint32  x0, y0;
        uint32  x1, y1;
        uint8  i;

        /* 入口参数过滤 */
        if (0 == no) return;
        if (1 == no)						// 单点
        {
            x0 = *points++;
            y0 = *points;
            Draw_Pixel(x0, y0);
        }

        /* 画多条线条 */
        x0 = *points++;					// 取出第一点坐标值，作为原起点坐标值
        y0 = *points++;
        for (i = 1; i < no; i++)
        {
            x1 = *points++;				// 取出下一点坐标值
            y1 = *points++;
            Draw_Line(x0, y0, x1, y1);
            x0 = x1;						// 更新原起点坐标
            y0 = y1;
        }
    }
    void  OLED_GFX::Draw_LineS(int16* points, uint8 no, uint16_t color)
    {
        uint32  x0, y0;
        uint32  x1, y1;
        uint8  i;

        /* 入口参数过滤 */
        if (0 == no) return;
        if (1 == no)						// 单点
        {
            x0 = *points++;
            y0 = *points;
            Draw_Pixel(x0, y0, color);
        }

        /* 画多条线条 */
        x0 = *points++;					// 取出第一点坐标值，作为原起点坐标值
        y0 = *points++;
        for (i = 1; i < no; i++)
        {
            x1 = *points++;				// 取出下一点坐标值
            y1 = *points++;
            Draw_Line(x0, y0, x1, y1, color);
            x0 = x1;						// 更新原起点坐标
            y0 = y1;
        }
    }

    void OLED_GFX::Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) {

        int16_t steep = abs(y1 - y0) > abs(x1 - x0);

        if (steep) {
            swapl(x0, y0);
            swapl(x1, y1);
        }
        if (x0 > x1) {
            swapl(x0, x1);
            swapl(y0, y1);
        }

        int16_t dx, dy;
        dx = x1 - x0;
        dy = abs(y1 - y0);

        int16_t err = dx / 2;
        int16_t ystep;

        if (y0 < y1) {
            ystep = 1;
        }
        else {
            ystep = -1;
        }

        for (; x0 <= x1; x0++) {
            if (steep)
                Draw_Pixel(y0, x0);
            else
                Draw_Pixel(x0, y0);
            err -= dy;

            if (err < 0) {
                y0 += ystep;
                err += dx;
            }
        }
    }

    void OLED_GFX::Write_Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {

        int16_t steep = abs(y1 - y0) > abs(x1 - x0);

        if (steep) {
            swapl(x0, y0);
            swapl(x1, y1);
        }
        if (x0 > x1) {
            swapl(x0, x1);
            swapl(y0, y1);
        }

        int16_t dx, dy;
        dx = x1 - x0;
        dy = abs(y1 - y0);

        int16_t err = dx / 2;
        int16_t ystep;

        if (y0 < y1) {
            ystep = 1;
        }
        else {
            ystep = -1;
        }

        for (; x0 <= x1; x0++) {
            if (steep)
                Draw_Pixel(y0, x0, color);
            else
                Draw_Pixel(x0, y0, color);
            err -= dy;

            if (err < 0) {
                y0 += ystep;
                err += dx;
            }
        }
    }

    // Draw a rectangle
    void OLED_GFX::Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h) {

        Draw_FastHLine(x, y, w);
        Draw_FastHLine(x, y + h, w);
        Draw_FastVLine(x, y, h);
        Draw_FastVLine(x + w, y, h);
    }
    // Draw a rectangle
    void OLED_GFX::Draw_Rect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {

        Draw_FastHLine(x, y, w, color);
        Draw_FastHLine(x, y + h, w, color);
        Draw_FastVLine(x, y, h, color);
        Draw_FastVLine(x + w, y, h, color);
    }

    /**************************************************************************/
    /*!
        @brief  Draws a filled rectangle using HW acceleration
    */
    /**************************************************************************/
    void OLED_GFX::Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {

        uint16_t i, j;
        if ((x >= SCR_WIDTH) || (y >= SCR_HEIGHT))
            return;

        // Y bounds check
        if (y + h > SCR_HEIGHT) {
            h = SCR_HEIGHT - y;
        }

        // X bounds check
        if (x + w > SCR_WIDTH) {
            w = SCR_WIDTH - x;
        }

        for (i = x; i <= w + x; i++)
            for (j = y; j <= h + y; j++)
                Draw_Pixel(i, j);
    }

    /**************************************************************************/
    /*!
        @brief  Draws a filled rectangle using HW acceleration
    */
    /**************************************************************************/
    void OLED_GFX::Fill_Rect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {

        uint16_t i, j;
        if ((x >= SCR_WIDTH) || (y >= SCR_HEIGHT))
            return;

        // Y bounds check
        if (y + h > SCR_HEIGHT) {
            h = SCR_HEIGHT - y;
        }

        // X bounds check
        if (x + w > SCR_WIDTH) {
            w = SCR_WIDTH - x;
        }

        for (i = x; i <= w + x; i++)
            for (j = y; j <= h + y; j++)
                Draw_Pixel(i, j, color);
    }
    void OLED_GFX::Fill_Circle(int16_t x0, int16_t y0, int16_t r) {

        Draw_FastVLine(x0, y0 - r, 2 * r);
        FillCircle_Helper(x0, y0, r, 3, 0);
    }
    void OLED_GFX::Fill_Circle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {

        Draw_FastVLine(x0, y0 - r, 2 * r, color);
        FillCircle_Helper(x0, y0, r, 3, 0, color);
    }

    // Used to do circles and roundrects
    void OLED_GFX::FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta) {

        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            if (corner & 0x1) {
                Draw_FastVLine(x0 + x, y0 - y, 2 * y + delta);
                Draw_FastVLine(x0 + y, y0 - x, 2 * x + delta);
            }
            if (corner & 0x2) {
                Draw_FastVLine(x0 - x, y0 - y, 2 * y + delta);
                Draw_FastVLine(x0 - y, y0 - x, 2 * x + delta);
            }
        }
    }

    // Used to do circles and roundrects
    void OLED_GFX::FillCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, int16_t delta, uint16_t color) {

        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            if (corner & 0x1) {
                Draw_FastVLine(x0 + x, y0 - y, 2 * y + delta, color);
                Draw_FastVLine(x0 + y, y0 - x, 2 * x + delta, color);
            }
            if (corner & 0x2) {
                Draw_FastVLine(x0 - x, y0 - y, 2 * y + delta, color);
                Draw_FastVLine(x0 - y, y0 - x, 2 * x + delta, color);
            }
        }
    }

    // Draw a circle outline
    void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        Draw_Pixel(x0, y0 + r);
        Draw_Pixel(x0, y0 - r);
        Draw_Pixel(x0 + r, y0);
        Draw_Pixel(x0 - r, y0);

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            Draw_Pixel(x0 + x, y0 + y);
            Draw_Pixel(x0 - x, y0 + y);
            Draw_Pixel(x0 + x, y0 - y);
            Draw_Pixel(x0 - x, y0 - y);
            Draw_Pixel(x0 + y, y0 + x);
            Draw_Pixel(x0 - y, y0 + x);
            Draw_Pixel(x0 + y, y0 - x);
            Draw_Pixel(x0 - y, y0 - x);
        }
    }
    // Draw a circle outline
    void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        Draw_Pixel(x0, y0 + r, color);
        Draw_Pixel(x0, y0 - r, color);
        Draw_Pixel(x0 + r, y0, color);
        Draw_Pixel(x0 - r, y0, color);

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            Draw_Pixel(x0 + x, y0 + y, color);
            Draw_Pixel(x0 - x, y0 + y, color);
            Draw_Pixel(x0 + x, y0 - y, color);
            Draw_Pixel(x0 - x, y0 - y, color);
            Draw_Pixel(x0 + y, y0 + x, color);
            Draw_Pixel(x0 - y, y0 + x, color);
            Draw_Pixel(x0 + y, y0 - x, color);
            Draw_Pixel(x0 - y, y0 - x, color);
        }
    }

    void OLED_GFX::Draw_Circle(int16_t x0, int16_t y0, int16_t r, uint8_t Type, uint16_t color) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;
        switch (Type)
        {
        case 1:
            Draw_Pixel(x0, y0 + r, color);
            Draw_Pixel(x0 + r, y0, color); break;//右下
        case 2:
            Draw_Pixel(x0, y0 + r, color);
            Draw_Pixel(x0 - r, y0, color); break;//左下
        case 3:
            Draw_Pixel(x0, y0 - r, color);
            Draw_Pixel(x0 + r, y0, color); break;//右上
        case 4:
            Draw_Pixel(x0 - r, y0, color);
            Draw_Pixel(x0, y0 - r, color); break;//左上
        }

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;

            switch (Type)
            {
            case 1:
                Draw_Pixel(x0 + x, y0 + y, color);
                Draw_Pixel(x0 + y, y0 + x, color); break;
            case 2:
                Draw_Pixel(x0 - x, y0 + y, color);
                Draw_Pixel(x0 - y, y0 + x, color); break;
            case 3:
                Draw_Pixel(x0 + x, y0 - y, color);
                Draw_Pixel(x0 + y, y0 - x, color); break;
            case 4:
                Draw_Pixel(x0 - y, y0 - x, color);
                Draw_Pixel(x0 - x, y0 - y, color); break;
            }



        }
    }

    // Draw a rounded rectangle
    void OLED_GFX::Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r) {
        // smarter version

        Draw_FastHLine(x + r, y, w - 2 * r); // Top
        Draw_FastHLine(x + r, y + h - 1, w - 2 * r); // Bottom
        Draw_FastVLine(x, y + r, h - 2 * r); // Left
        Draw_FastVLine(x + w - 1, y + r, h - 2 * r); // Right
        // draw four corners
        DrawCircle_Helper(x + r, y + r, r, 1);
        DrawCircle_Helper(x + w - r - 1, y + r, r, 2);
        DrawCircle_Helper(x + w - r - 1, y + h - r - 1, r, 4);
        DrawCircle_Helper(x + r, y + h - r - 1, r, 8);
    }
    // Draw a rounded rectangle
    void OLED_GFX::Draw_RoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
        // smarter version

        Draw_FastHLine(x + r, y, w - 2 * r, color); // Top
        Draw_FastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
        Draw_FastVLine(x, y + r, h - 2 * r, color); // Left
        Draw_FastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
        // draw four corners
        DrawCircle_Helper(x + r, y + r, r, 1, color);
        DrawCircle_Helper(x + w - r - 1, y + r, r, 2, color);
        DrawCircle_Helper(x + w - r - 1, y + h - r - 1, r, 4, color);
        DrawCircle_Helper(x + r, y + h - r - 1, r, 8, color);
    }

    void OLED_GFX::DrawCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;
            if (corner & 0x4) {
                Draw_Pixel(x0 + x, y0 + y);
                Draw_Pixel(x0 + y, y0 + x);
            }
            if (corner & 0x2) {
                Draw_Pixel(x0 + x, y0 - y);
                Draw_Pixel(x0 + y, y0 - x);
            }
            if (corner & 0x8) {
                Draw_Pixel(x0 - y, y0 + x);
                Draw_Pixel(x0 - x, y0 + y);
            }
            if (corner & 0x1) {
                Draw_Pixel(x0 - y, y0 - x);
                Draw_Pixel(x0 - x, y0 - y);
            }
        }
    }


    void OLED_GFX::DrawCircle_Helper(int16_t x0, int16_t y0, int16_t r, uint8_t corner, uint16_t color) {
        int16_t f = 1 - r;
        int16_t ddF_x = 1;
        int16_t ddF_y = -2 * r;
        int16_t x = 0;
        int16_t y = r;

        while (x < y) {
            if (f >= 0) {
                y--;
                ddF_y += 2;
                f += ddF_y;
            }
            x++;
            ddF_x += 2;
            f += ddF_x;
            if (corner & 0x4) {
                Draw_Pixel(x0 + x, y0 + y, color);
                Draw_Pixel(x0 + y, y0 + x, color);
            }
            if (corner & 0x2) {
                Draw_Pixel(x0 + x, y0 - y, color);
                Draw_Pixel(x0 + y, y0 - x, color);
            }
            if (corner & 0x8) {
                Draw_Pixel(x0 - y, y0 + x, color);
                Draw_Pixel(x0 - x, y0 + y, color);
            }
            if (corner & 0x1) {
                Draw_Pixel(x0 - y, y0 - x, color);
                Draw_Pixel(x0 - x, y0 - y, color);
            }
        }
    }

    // Draw a triangle
    void OLED_GFX::Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2) {
        Draw_Line(x0, y0, x1, y1);
        Draw_Line(x1, y1, x2, y2);
        Draw_Line(x2, y2, x0, y0);
    }
    // Draw a triangle
    void OLED_GFX::Draw_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
        Draw_Line(x0, y0, x1, y1, color);
        Draw_Line(x1, y1, x2, y2, color);
        Draw_Line(x2, y2, x0, y0, color);
    }
    void OLED_GFX::Fill_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2)
    {

        int16_t a, b, y, last;
        // Sort coordinates by Y order (y2 >= y1 >= y0)
        if (y0 > y1)
        {
            swapl(y0, y1);
            swapl(x0, x1);
        }
        if (y1 > y2)
        {
            swapl(y2, y1);
            swapl(x2, x1);
        }
        if (y0 > y1)
        {
            swapl(y0, y1);
            swapl(x0, x1);
        }

        if (y0 == y2)
        {
            // Handle awkward all-on-same-line case as its own thing
            a = b = x0;
            if (x1 < a)
            {
                a = x1;
            }
            else if (x1 > b)
            {
                b = x1;
            }
            if (x2 < a)
            {
                a = x2;
            }
            else if (x2 > b)
            {
                b = x2;
            }
            Draw_FastHLine(a, y0, b - a);
            return;
        }

        int16_t dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1,
            sa = 0,
            sb = 0;

        // For upper part of triangle, find scanline crossings for segments
        // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
        // is included here (and second loop will be skipped, avoiding a /0
        // error there), otherwise scanline y1 is skipped here and handled
        // in the second loop...which also avoids a /0 error here if y0=y1
        // (flat-topped triangle).
        if (y1 == y2)
        {
            last = y1;   // Include y1 scanline
        }
        else
        {
            last = y1 - 1; // Skip it
        }


        for (y = y0; y <= last; y++)
        {
            a = x0 + sa / dy01;
            b = x0 + sb / dy02;
            sa += dx01;
            sb += dx02;

            if (a > b)
            {
                swapl(a, b);
            }

            Draw_FastHLine(a, y, b - a);
        }

        // For lower part of triangle, find scanline crossings for segments
        // 0-2 and 1-2.  This loop is skipped if y1=y2.
        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);

        for (; y <= y2; y++)
        {
            a = x1 + sa / dy12;
            b = x0 + sb / dy02;
            sa += dx12;
            sb += dx02;

            if (a > b)
            {
                swapl(a, b);
            }

            Draw_FastHLine(a, y, b - a);
        }
    }
    void OLED_GFX::Fill_Triangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color)
    {

        int16_t a, b, y, last;
        // Sort coordinates by Y order (y2 >= y1 >= y0)
        if (y0 > y1)
        {
            swapl(y0, y1);
            swapl(x0, x1);
        }
        if (y1 > y2)
        {
            swapl(y2, y1);
            swapl(x2, x1);
        }
        if (y0 > y1)
        {
            swapl(y0, y1);
            swapl(x0, x1);
        }

        if (y0 == y2)
        {
            // Handle awkward all-on-same-line case as its own thing
            a = b = x0;
            if (x1 < a)
            {
                a = x1;
            }
            else if (x1 > b)
            {
                b = x1;
            }
            if (x2 < a)
            {
                a = x2;
            }
            else if (x2 > b)
            {
                b = x2;
            }
            Draw_FastHLine(a, y0, b - a, color);
            return;
        }

        int16_t dx01 = x1 - x0,
            dy01 = y1 - y0,
            dx02 = x2 - x0,
            dy02 = y2 - y0,
            dx12 = x2 - x1,
            dy12 = y2 - y1,
            sa = 0,
            sb = 0;

        // For upper part of triangle, find scanline crossings for segments
        // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
        // is included here (and second loop will be skipped, avoiding a /0
        // error there), otherwise scanline y1 is skipped here and handled
        // in the second loop...which also avoids a /0 error here if y0=y1
        // (flat-topped triangle).
        if (y1 == y2)
        {
            last = y1;   // Include y1 scanline
        }
        else
        {
            last = y1 - 1; // Skip it
        }


        for (y = y0; y <= last; y++)
        {
            a = x0 + sa / dy01;
            b = x0 + sb / dy02;
            sa += dx01;
            sb += dx02;

            if (a > b)
            {
                swapl(a, b);
            }

            Draw_FastHLine(a, y, b - a, color);
        }

        // For lower part of triangle, find scanline crossings for segments
        // 0-2 and 1-2.  This loop is skipped if y1=y2.
        sa = dx12 * (y - y1);
        sb = dx02 * (y - y0);

        for (; y <= y2; y++)
        {
            a = x1 + sa / dy12;
            b = x0 + sb / dy02;
            sa += dx12;
            sb += dx02;

            if (a > b)
            {
                swapl(a, b);
            }

            Draw_FastHLine(a, y, b - a, color);
        }
    }

#ifdef __cplusplus
}
#endif


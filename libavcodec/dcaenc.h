﻿/*
 * DCA encoder tables
 * Copyright (C) 2008-2012 Alexander E. Patrakov
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_DCAENC_H
#define AVCODEC_DCAENC_H

#include <stdint.h>

typedef struct {
    int32_t m;
    int32_t e;
} softfloat;

static const int sample_rates[] = {
    8000, 16000, 32000, 11025, 22050, 44100, 12000, 24000, 48000, 0,
};

static const uint8_t bitstream_sfreq[] = { 1, 2, 3, 6, 7, 8, 11, 12, 13 };

/* Auditory filter center frequencies and bandwidths, in Hz.
 * The last two are made up, because there is no scientific data.
 */
static const uint16_t fc[] = {
    50, 150, 250, 350, 450, 570, 700, 840, 1000, 1170, 1370, 1600, 1850, 2150,
    2500, 2900, 3400, 4000, 4800, 5800, 7000, 8500, 10500, 13500, 17000
};

static const uint16_t erb[] = {
    80, 100, 100, 100, 110, 120, 140, 150, 160, 190, 210, 240, 280,
    320, 380, 450, 550, 700, 900, 1100, 1300, 1800, 2500, 3500, 4500
};

static const softfloat stepsize_inv[27] = {
    {0, 0}, {1342177360, 21}, {2147483647, 21}, {1342177360, 20},
    {1819901661, 20}, {2147483647, 20}, {1278263843, 19}, {1579032492, 19},
    {1412817763, 18}, {1220162327, 17}, {1118482133, 16}, {1917391412, 16},
    {1766017772, 15}, {1525212826, 14}, {1290553940, 13}, {2097179000, 13},
    {1677683200, 12}, {1497972244, 11}, {1310893147, 10}, {1165354136, 9},
    {1748031204, 9}, {1542092044, 8}, {1636178017, 7}, {1636178017, 6},
    {1636178017, 5}, {1636178017, 4}, {1636178017, 3},
};

static const softfloat scalefactor_inv[128] = {
    {2147483647, 1}, {2147483647, 1}, {2147483647, 2}, {2147483647, 2},
    {2147483647, 2}, {2147483647, 2}, {1431655765, 2}, {1431655765, 2},
    {1431655765, 2}, {2147483647, 3}, {2147483647, 3}, {1717986918, 3},
    {1431655765, 3}, {1227133513, 3}, {1227133513, 3}, {2147483647, 4},
    {1717986918, 4}, {1561806289, 4}, {1431655765, 4}, {1227133513, 4},
    {2147483647, 5}, {1908874353, 5}, {1717986918, 5}, {1493901668, 5},
    {1321528398, 5}, {1145324612, 5}, {2021161080, 6}, {1808407282, 6},
    {1561806289, 6}, {1374389534, 6}, {1227133513, 6}, {2147483647, 7},
    {1908874353, 7}, {1676084798, 7}, {1477838209, 7}, {1296593900, 7},
    {1145324612, 7}, {2021161080, 8}, {1773405851, 8}, {1561806289, 8},
    {1374389534, 8}, {1216273924, 8}, {2139127680, 9}, {1882725390, 9},
    {1660893697, 9}, {1462116526, 9}, {1287484341, 9}, {1135859119, 9},
    {1999112050, 10}, {1762037865, 10}, {1552982525, 10}, {1367551775, 10},
    {1205604855, 10}, {2124660150, 11}, {1871509153, 11}, {1648443220, 11},
    {1452459217, 11}, {1279990253, 11}, {1127704233, 11}, {1987368509, 12},
    {1750814693, 12}, {1542632939, 12}, {1359099663, 12}, {1197398995, 12},
    {2109880792, 13}, {1858853132, 13}, {1638006149, 13}, {1443165385, 13},
    {1271479187, 13}, {1120235993, 13}, {1973767086, 14}, {1739045674, 14},
    {1532153461, 14}, {1349922194, 14}, {1189384493, 14}, {2095804865, 15},
    {1846464029, 15}, {1626872524, 15}, {1433347133, 15}, {1262853884, 15},
    {1112619678, 15}, {1960569045, 16}, {1727349015, 16}, {1521881227, 16},
    {1340842289, 16}, {1181357555, 16}, {2081669156, 17}, {1834047752, 17},
    {1615889229, 17}, {1423675973, 17}, {1254322457, 17}, {1105123583, 17},
    {1947330755, 18}, {1715693602, 18}, {1511607799, 18}, {1331801790, 18},
    {1173384427, 18}, {2067616532, 19}, {1821667648, 19}, {1604980024, 19},
    {1414066955, 19}, {1245861410, 19}, {1097665748, 19}, {1934193616, 20},
    {1704119624, 20}, {1501412075, 20}, {1322817107, 20}, {1165466323, 20},
    {2053666205, 21}, {1809379407, 21}, {1594151671, 21}, {1404526328, 21},
    {1237455941, 21}, {1090259329, 21}, {1921143210, 22}, {1692621231, 22},
    {1491281857, 22}, {1313892269, 22}, {1157603482, 22}, {2039810470, 23},
    {1797172644, 23}, {1583396912, 23}, {1395050052, 23}, {1229107276, 23},
    {1082903494, 23}, {1082903494, 23}, {1082903494, 23}, {1082903494, 23},
};

/* manually derived from
 * Table B.5: Selection of quantization levels and codebooks
 */
static const int bit_consumption[27] = {
    -8, 28, 40, 48, 52, 60, 68, 76, 80, 96,
    112, 128, 144, 160, 176, 192, 208, 224, 240, 256,
    272, 288, 304, 320, 336, 352, 368,
};

static const int8_t lfe_index[16] = {
    1, 2, 2, 2, 2, 3, 2, 3, 2, 3, 2, 3, 1, 3, 2, 3
};

static const int8_t channel_reorder_lfe[16][9] = {
    { 0, -1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 2,  0,  1, -1, -1, -1, -1, -1, -1 },
    { 0,  1,  3, -1, -1, -1, -1, -1, -1 },
    { 2,  0,  1,  4, -1, -1, -1, -1, -1 },
    { 0,  1,  3,  4, -1, -1, -1, -1, -1 },
    { 2,  0,  1,  4,  5, -1, -1, -1, -1 },
    { 3,  4,  0,  1,  5,  6, -1, -1, -1 },
    { 2,  0,  1,  4,  5,  6, -1, -1, -1 },
    { 0,  6,  4,  5,  2,  3, -1, -1, -1 },
    { 4,  2,  5,  0,  1,  6,  7, -1, -1 },
    { 5,  6,  0,  1,  7,  3,  8,  4, -1 },
    { 4,  2,  5,  0,  1,  6,  8,  7, -1 },
};

static const int8_t channel_reorder_nolfe[16][9] = {
    { 0, -1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 0,  1, -1, -1, -1, -1, -1, -1, -1 },
    { 2,  0,  1, -1, -1, -1, -1, -1, -1 },
    { 0,  1,  2, -1, -1, -1, -1, -1, -1 },
    { 2,  0,  1,  3, -1, -1, -1, -1, -1 },
    { 0,  1,  2,  3, -1, -1, -1, -1, -1 },
    { 2,  0,  1,  3,  4, -1, -1, -1, -1 },
    { 2,  3,  0,  1,  4,  5, -1, -1, -1 },
    { 2,  0,  1,  3,  4,  5, -1, -1, -1 },
    { 0,  5,  3,  4,  1,  2, -1, -1, -1 },
    { 3,  2,  4,  0,  1,  5,  6, -1, -1 },
    { 4,  5,  0,  1,  6,  2,  7,  3, -1 },
    { 3,  2,  4,  0,  1,  5,  7,  6, -1 },
};

#endif /* AVCODEC_DCAENC_H */

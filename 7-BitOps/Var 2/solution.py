z1 = 0x770a # (x >> 1) ^ z
z2 = 0x1fea # z | (y >> 1)
z3 = 0x0ac0  # (x >> 1) & y
z4 = 0xddd5 # x | z

# trying z4
print(f"{bin(z4)[2:].zfill(16)}") 
# 1101110111010101

# x         = ??0???0???0?0?0?
# z         = ??0???0???0?0?0?
#           = 1101110111010101
#
# newx      = ??0???0???0?0?0?
# newz      = ??0???0???0?0?0?


# trying z1
print(f"{bin(z1)[2:].zfill(16)}")
# 0111011100001010

# x >> 1    = 0?10??10??001010
# z         = 0?01??01??000000
#           = 0111011100001010
#
# newx      = ?10??10??001010?
# newz      = 0?01??01??000000


# trying z3
print(hex(z3))
print(f"{bin(z3)[2:].zfill(16)}")
# 0000101011000000

# x >> 1    = 0?101?1011001010
# y         = ??001?1?11??0?0?
#           = 0000101011000000
#
# newx      = ?101?1011001010?
# newy      = ??001?1?11??0?0?

# trying z2
print(bin(z2)[2:].zfill(16))
# 0001111111101010

# z         = 00011?01??000000
# y >> 1    = 00000111?1101010
#           = 0001111111101010
# 
# newz      = 00011?01??000000
# newy      = 0000111?1101010?

# ============================
# creating checkpoint
# x         = ?101?1011001010?
# y         = 0000111?1101010?
# z         = 00011?01??000000
# ============================

# fitting again
# z4
# x         = 1101?10110010101
# z         = 00011?01?1000000
#           = 1101110111010101
#
# newx      = 1101?10110010101
# newz      = 00011?01?1000000


# z1
# x >> 1    = 01101?1011001010
# z         = 00011?0101000000
#           = 0111011100001010
#
# newx      = 1101?10110010101
# newz      = 00011?0101000000

# ============================
# creating checkpoint
# x         = 1101?10110010101
# y         = 0000111?1101010?
# z         = 00011?0101000000
# ============================

# z3
# x >> 1    = 01101?1011001010
# y         = 1101110110010101
#           = 0000101011000000

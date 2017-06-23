#!/usr/bin/python
# -*- coding: UTF-8 -*-

from fractions import gcd
import sys
import random
from check_probable_prime import is_probable_prime
import time

# 扩展欧几里德算法
def ext_euclid(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = ext_euclid(b % a, a)
        return (g, x - (b // a) * y, y)

# 用扩展欧几里德算法计算 a 对于 m 的欧拉函数值的模反元素
def modinv(a, m):
    g, x, y = ext_euclid(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

# Square-and-Multiply 加速次方乘法
def square_multiply(x, exponents):
    exponentsList = [int(m) for m in list('{0:0b}'.format(exponents))]
    exponentsList.reverse()
    del exponentsList[0]
    y = x
    for exp in exponentsList:
        y = pow(y, 2)
        if (exp == 1):
            y = y * x
    return y

def rsa_encrypt(plaintext , keylength):
    # 程序计时开始
    tStart = time.time()

    # 设置消息
    messsage = plaintext
    # 设置密钥key长度
    # keylength = 1024
    q_length = keylength / 2
    p_length = q_length - 2

    # 利用 Square-and-Multiply 加速次方乘法计算，并通过 Miller-Rabin Test 选择两个大质数
    p = 2
    q = 2
    left_p_length = square_multiply(2, p_length - 1)
    right_p_length = square_multiply(2, p_length)

    left_q_length = square_multiply(2, q_length - 1)
    right_q_length = square_multiply(2, q_length)

    is_prime = True
    while is_prime:
        rand = random.randint(left_p_length , right_p_length)
        if is_probable_prime(rand):
            is_prime = False
            p = rand

    is_prime = True
    while is_prime:
        rand = random.randint(left_q_length , right_q_length)
        if is_probable_prime(rand):
            is_prime =  False
            q = rand

    # 质数相乘得到n
    n = p * q

    # 检查明文长度是否超过key
    if len(str(n)) < len(str(messsage)):
    	raise Exception('message(' + str(len(str(messsage))) + \
    		') 不能比 n(' + str(len(str(n))) + ') 還要長')

    # 计算n的欧拉函数值 φ(n)
    # φ(n) = (p-1)(q-1)
    phi = (p - 1) * (q - 1)

    # 随机选择一个较小范围的 2～keylength 范围内的数作为step
    # 求出在 1 < e < φ(n) AND gcd( e, φ(n) ) = 1 条件下与φ(n)互质的数 e
    # small public exponent e (public key)
    e = 0
    i = 2
    while (i < phi):
        step = random.randint(2, keylength)
        if gcd( i, phi ) == 1:
    		         e = i
    		         break
        i = i + step

    # 利用拓展欧几里德算法计算 e 对于 φ(n) 的模反元素
    d = modinv( e, phi );


    # 待加密的明文（数字）
    plain = messsage

    # 使用公钥(n,e)加密
    cipher = pow( plain, e, n )

    # 计时结束
    tEnd = time.time()
    timeEncrypt = tEnd - tStart
    return p, q, n, e, d, plain, cipher, timeEncrypt

def rsa_decrypt(d, p, q, cipher):
        # 计时结束
        tStart = time.time()
        # 方法一：使用 CRT 中国余数定理加速解密
        dp = d%(p-1)
        dq = d%(q-1)
        qp = modinv(q , p) % p
        m1 = pow(cipher%p, dp , p)
        m2 = pow(cipher%q, dq , q)
        h = (qp * (m1 - m2)) %p
        decrypted = m2 + h*q
        # 计时结束
        tEnd = time.time()
        # 方法二：使用私钥(n,d)直接解密
        # decrypted = pow( cipher, d, n)
        timeDecrypt = tEnd - tStart
        return timeDecrypt,decrypted


# 以下是单独执行该 program 时可以输出结果
# p, q, n, e, d, plain, cipher, timeEncrypt = rsa_encrypt(20170528, 1024)
# timeDecrypt, decrypted  = rsa_decrypt(d, p, q, cipher)

# 打印结果
# print "\n--------- The length of Key(Bit) ---------"
# print "1.  The length of Key(Bit) : " + str(len(bin(n))) + "\n"
#
# print "--------- Cost Time ---------"
# print "2.1. Encypytion cost  %f  seconds" % timeEncrypt + "\n"
# print "2.2. Decryption cost  %f  seconds" % timeDecrypt + "\n"
#
# print "----------- Keys ------------"
# print "3.1. Public key (n,e) = (" + str(n) + ",\n" + str(e) + ")"
# print "3.1. Private key (n,d) = (" + str(n) + ",\n" + str(d) + ")"
#
# print "---------- Messages ---------"
# print "4. Plain: " + str(plain)
# print "5. After Encrypted: " + str(cipher)
# if plain == decrypted:
# 	print "6. After Decrypted: " + str(decrypted) + " (Correct)"
# else:
# 	print "6. After Decrypted: " + str(decrypted) + " (Failed)"
# print "----------- End -------------"

riscv32-unknown-elf-objdump -Mmarch=rv32imcxgap9 -d /scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/L2_check/build/lfsr32/lfsr32

/scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/L2_check/build/lfsr32/lfsr32:     file format elf32-littleriscv


Disassembly of section .vectors:

1c008000 <__irq_vector_base>:
1c008000:	29a0106f          	j	1c00929a <__rt_handle_illegal_instr>
1c008004:	0840006f          	j	1c008088 <pos_no_irq_handler>
1c008008:	0800006f          	j	1c008088 <pos_no_irq_handler>
1c00800c:	07c0006f          	j	1c008088 <pos_no_irq_handler>
1c008010:	0780006f          	j	1c008088 <pos_no_irq_handler>
1c008014:	0740006f          	j	1c008088 <pos_no_irq_handler>
1c008018:	0700006f          	j	1c008088 <pos_no_irq_handler>
1c00801c:	06c0006f          	j	1c008088 <pos_no_irq_handler>
1c008020:	0680006f          	j	1c008088 <pos_no_irq_handler>
1c008024:	0640006f          	j	1c008088 <pos_no_irq_handler>
1c008028:	0600006f          	j	1c008088 <pos_no_irq_handler>
1c00802c:	05c0006f          	j	1c008088 <pos_no_irq_handler>
1c008030:	0580006f          	j	1c008088 <pos_no_irq_handler>
1c008034:	0540006f          	j	1c008088 <pos_no_irq_handler>
1c008038:	0500006f          	j	1c008088 <pos_no_irq_handler>
1c00803c:	04c0006f          	j	1c008088 <pos_no_irq_handler>
1c008040:	0480006f          	j	1c008088 <pos_no_irq_handler>
1c008044:	0440006f          	j	1c008088 <pos_no_irq_handler>
1c008048:	0400006f          	j	1c008088 <pos_no_irq_handler>
1c00804c:	03c0006f          	j	1c008088 <pos_no_irq_handler>
1c008050:	0380006f          	j	1c008088 <pos_no_irq_handler>
1c008054:	0340006f          	j	1c008088 <pos_no_irq_handler>
1c008058:	0300006f          	j	1c008088 <pos_no_irq_handler>
1c00805c:	02c0006f          	j	1c008088 <pos_no_irq_handler>
1c008060:	0280006f          	j	1c008088 <pos_no_irq_handler>
1c008064:	0240006f          	j	1c008088 <pos_no_irq_handler>
1c008068:	0200006f          	j	1c008088 <pos_no_irq_handler>
1c00806c:	01c0006f          	j	1c008088 <pos_no_irq_handler>
1c008070:	0180006f          	j	1c008088 <pos_no_irq_handler>
1c008074:	0140006f          	j	1c008088 <pos_no_irq_handler>
1c008078:	0100006f          	j	1c008088 <pos_no_irq_handler>
1c00807c:	00c0006f          	j	1c008088 <pos_no_irq_handler>

1c008080 <_start>:
1c008080:	0640006f          	j	1c0080e4 <_stext>

1c008084 <pos_illegal_instr>:
1c008084:	2160106f          	j	1c00929a <__rt_handle_illegal_instr>

1c008088 <pos_no_irq_handler>:
1c008088:	30200073          	mret

1c00808c <pos_semihosting_call>:
1c00808c:	00100073          	ebreak
1c008090:	00008067          	ret

1c008094 <pe_start>:
1c008094:	f3ff8117          	auipc	sp,0xf3ff8
1c008098:	f7010113          	addi	sp,sp,-144 # 10000004 <cluster_stacks>
1c00809c:	00012103          	lw	sp,0(sp)
1c0080a0:	000011b7          	lui	gp,0x1
1c0080a4:	80018193          	addi	gp,gp,-2048 # 800 <__cluster_text_size+0x800>
1c0080a8:	00158593          	addi	a1,a1,1
1c0080ac:	02b180b3          	mul	ra,gp,a1
1c0080b0:	00110133          	add	sp,sp,ra
1c0080b4:	2640106f          	j	1c009318 <cluster_entry_stub>

1c0080b8 <do_cl_boot>:
1c0080b8:	10200137          	lui	sp,0x10200
1c0080bc:	00100193          	li	gp,1
1c0080c0:	00000217          	auipc	tp,0x0
1c0080c4:	fc020213          	addi	tp,tp,-64 # 1c008080 <_start>
1c0080c8:	04412023          	sw	tp,64(sp) # 10200040 <__l2_shared_end+0x200038>
1c0080cc:	00312423          	sw	gp,8(sp)

1c0080d0 <loop>:
1c0080d0:	1a10a137          	lui	sp,0x1a10a
1c0080d4:	80010113          	addi	sp,sp,-2048 # 1a109800 <__l2_shared_end+0xa1097f8>
1c0080d8:	00012023          	sw	zero,0(sp)
1c0080dc:	10500073          	wfi
1c0080e0:	ff1ff06f          	j	1c0080d0 <loop>

Disassembly of section .text:

1c0080e4 <_stext>:
1c0080e4:	f1402573          	csrr	a0,mhartid
1c0080e8:	01f57593          	andi	a1,a0,31
1c0080ec:	8115                	srli	a0,a0,0x5
1c0080ee:	467d                	li	a2,31
1c0080f0:	00c50463          	beq	a0,a2,1c0080f8 <_stext+0x14>
1c0080f4:	fa1ff06f          	j	1c008094 <pe_start>
1c0080f8:	ffff9297          	auipc	t0,0xffff9
1c0080fc:	b5828293          	addi	t0,t0,-1192 # 1c000c50 <_edata>
1c008100:	ffff9317          	auipc	t1,0xffff9
1c008104:	b8830313          	addi	t1,t1,-1144 # 1c000c88 <__l2_priv0_end>
1c008108:	0002a023          	sw	zero,0(t0)
1c00810c:	0291                	addi	t0,t0,4
1c00810e:	fe62ede3          	bltu	t0,t1,1c008108 <_stext+0x24>
1c008112:	ffff8117          	auipc	sp,0xffff8
1c008116:	73e10113          	addi	sp,sp,1854 # 1c000850 <stack>
1c00811a:	7e3000ef          	jal	ra,1c0090fc <pos_init_start>
1c00811e:	00000513          	li	a0,0
1c008122:	00000593          	li	a1,0
1c008126:	00000397          	auipc	t2,0x0
1c00812a:	05438393          	addi	t2,t2,84 # 1c00817a <main>
1c00812e:	000380e7          	jalr	t2
1c008132:	842a                	mv	s0,a0
1c008134:	01e010ef          	jal	ra,1c009152 <pos_init_stop>
1c008138:	8522                	mv	a0,s0
1c00813a:	310000ef          	jal	ra,1c00844a <exit>

1c00813e <lfsr_iter_word>:
1c00813e:	ee853733          	p.bclr	a4,a0,23,8
1c008142:	070a                	slli	a4,a4,0x2
1c008144:	20e5f703          	p.lw	a4,a4(a1)
1c008148:	8121                	srli	a0,a0,0x8
1c00814a:	8d39                	xor	a0,a0,a4
1c00814c:	ee853733          	p.bclr	a4,a0,23,8
1c008150:	070a                	slli	a4,a4,0x2
1c008152:	20e5f703          	p.lw	a4,a4(a1)
1c008156:	8121                	srli	a0,a0,0x8
1c008158:	8f29                	xor	a4,a4,a0
1c00815a:	ee8737b3          	p.bclr	a5,a4,23,8
1c00815e:	078a                	slli	a5,a5,0x2
1c008160:	20f5f503          	p.lw	a0,a5(a1)
1c008164:	00875793          	srli	a5,a4,0x8
1c008168:	8fa9                	xor	a5,a5,a0
1c00816a:	ee87b533          	p.bclr	a0,a5,23,8
1c00816e:	050a                	slli	a0,a0,0x2
1c008170:	20a5f503          	p.lw	a0,a0(a1)
1c008174:	83a1                	srli	a5,a5,0x8
1c008176:	8d3d                	xor	a0,a0,a5
1c008178:	8082                	ret

1c00817a <main>:
1c00817a:	1101                	addi	sp,sp,-32
1c00817c:	deadc537          	lui	a0,0xdeadc
1c008180:	cc22                	sw	s0,24(sp)
1c008182:	ca26                	sw	s1,20(sp)
1c008184:	c84a                	sw	s2,16(sp)
1c008186:	ce06                	sw	ra,28(sp)
1c008188:	c64e                	sw	s3,12(sp)
1c00818a:	1c010437          	lui	s0,0x1c010
1c00818e:	eef50513          	addi	a0,a0,-273 # deadbeef <pulp__FC+0xdeadbef0>
1c008192:	1c001937          	lui	s2,0x1c001
1c008196:	1c0924b7          	lui	s1,0x1c092
1c00819a:	85090593          	addi	a1,s2,-1968 # 1c000850 <stack>
1c00819e:	3745                	jal	1c00813e <lfsr_iter_word>
1c0081a0:	00a4222b          	p.sw	a0,4(s0!) # 1c010004 <__cluster_text_end+0x4>
1c0081a4:	fe941be3          	bne	s0,s1,1c00819a <main+0x20>
1c0081a8:	deadc537          	lui	a0,0xdeadc
1c0081ac:	1c010437          	lui	s0,0x1c010
1c0081b0:	eef50513          	addi	a0,a0,-273 # deadbeef <pulp__FC+0xdeadbef0>
1c0081b4:	4481                	li	s1,0
1c0081b6:	1c0929b7          	lui	s3,0x1c092
1c0081ba:	85090593          	addi	a1,s2,-1968
1c0081be:	3741                	jal	1c00813e <lfsr_iter_word>
1c0081c0:	0044278b          	p.lw	a5,4(s0!) # 1c010004 <__cluster_text_end+0x4>
1c0081c4:	8fa9                	xor	a5,a5,a0
1c0081c6:	1007b7b3          	p.cnt	a5,a5
1c0081ca:	94be                	add	s1,s1,a5
1c0081cc:	ff3417e3          	bne	s0,s3,1c0081ba <main+0x40>
1c0081d0:	1c000537          	lui	a0,0x1c000
1c0081d4:	85a6                	mv	a1,s1
1c0081d6:	01c50513          	addi	a0,a0,28 # 1c00001c <__DTOR_END__>
1c0081da:	2469                	jal	1c008464 <printf>
1c0081dc:	40f2                	lw	ra,28(sp)
1c0081de:	4462                	lw	s0,24(sp)
1c0081e0:	8526                	mv	a0,s1
1c0081e2:	4942                	lw	s2,16(sp)
1c0081e4:	44d2                	lw	s1,20(sp)
1c0081e6:	49b2                	lw	s3,12(sp)
1c0081e8:	6105                	addi	sp,sp,32
1c0081ea:	8082                	ret

1c0081ec <pos_fll_set_freq>:
1c0081ec:	10059733          	p.fl1	a4,a1
1c0081f0:	47f5                	li	a5,29
1c0081f2:	82e7b7db          	p.subun	a5,a5,a4,1
1c0081f6:	872a                	mv	a4,a0
1c0081f8:	cfa9                	beqz	a5,1c008252 <pos_fll_set_freq+0x66>
1c0081fa:	fff78693          	addi	a3,a5,-1
1c0081fe:	4605                	li	a2,1
1c008200:	00d61633          	sll	a2,a2,a3
1c008204:	00178893          	addi	a7,a5,1
1c008208:	1c0016b7          	lui	a3,0x1c001
1c00820c:	c5068693          	addi	a3,a3,-944 # 1c000c50 <_edata>
1c008210:	00f595b3          	sll	a1,a1,a5
1c008214:	96ba                	add	a3,a3,a4
1c008216:	dc05b533          	p.bclr	a0,a1,14,0
1c00821a:	0006c803          	lbu	a6,0(a3)
1c00821e:	1c0016b7          	lui	a3,0x1c001
1c008222:	c0f6255b          	p.addunr	a0,a2,a5
1c008226:	c5c68693          	addi	a3,a3,-932 # 1c000c5c <pos_fll_freq>
1c00822a:	00271793          	slli	a5,a4,0x2
1c00822e:	00a6e7a3          	p.sw	a0,a5(a3)
1c008232:	00080f63          	beqz	a6,1c008250 <pos_fll_set_freq+0x64>
1c008236:	0712                	slli	a4,a4,0x4
1c008238:	0711                	addi	a4,a4,4
1c00823a:	1a1006b7          	lui	a3,0x1a100
1c00823e:	20e6f783          	p.lw	a5,a4(a3)
1c008242:	81bd                	srli	a1,a1,0xf
1c008244:	de05a7b3          	p.insert	a5,a1,15,0
1c008248:	c7a8a7b3          	p.insert	a5,a7,3,26
1c00824c:	00f6e723          	p.sw	a5,a4(a3)
1c008250:	8082                	ret
1c008252:	4889                	li	a7,2
1c008254:	4605                	li	a2,1
1c008256:	4785                	li	a5,1
1c008258:	bf45                	j	1c008208 <pos_fll_set_freq+0x1c>

1c00825a <pos_fll_init>:
1c00825a:	1141                	addi	sp,sp,-16
1c00825c:	00451693          	slli	a3,a0,0x4
1c008260:	c226                	sw	s1,4(sp)
1c008262:	00468613          	addi	a2,a3,4 # 1a100004 <__l2_shared_end+0xa0ffffc>
1c008266:	84aa                	mv	s1,a0
1c008268:	1a1007b7          	lui	a5,0x1a100
1c00826c:	c606                	sw	ra,12(sp)
1c00826e:	c422                	sw	s0,8(sp)
1c008270:	20c7f503          	p.lw	a0,a2(a5)
1c008274:	872a                	mv	a4,a0
1c008276:	04054163          	bltz	a0,1c0082b8 <pos_fll_init+0x5e>
1c00827a:	00868893          	addi	a7,a3,8
1c00827e:	2117f803          	p.lw	a6,a7(a5)
1c008282:	4599                	li	a1,6
1c008284:	caa5a833          	p.insert	a6,a1,5,10
1c008288:	05000593          	li	a1,80
1c00828c:	d705a833          	p.insert	a6,a1,11,16
1c008290:	1a1005b7          	lui	a1,0x1a100
1c008294:	0105e8a3          	p.sw	a6,a7(a1)
1c008298:	06b1                	addi	a3,a3,12
1c00829a:	20d7f783          	p.lw	a5,a3(a5)
1c00829e:	14c00813          	li	a6,332
1c0082a2:	d30827b3          	p.insert	a5,a6,9,16
1c0082a6:	00f5e6a3          	p.sw	a5,a3(a1)
1c0082aa:	4785                	li	a5,1
1c0082ac:	c1e7a733          	p.insert	a4,a5,0,30
1c0082b0:	c1f7a733          	p.insert	a4,a5,0,31
1c0082b4:	00e5e623          	p.sw	a4,a2(a1)
1c0082b8:	1c0016b7          	lui	a3,0x1c001
1c0082bc:	00249793          	slli	a5,s1,0x2
1c0082c0:	c5c68693          	addi	a3,a3,-932 # 1c000c5c <pos_fll_freq>
1c0082c4:	97b6                	add	a5,a5,a3
1c0082c6:	4380                	lw	s0,0(a5)
1c0082c8:	e41d                	bnez	s0,1c0082f6 <pos_fll_init+0x9c>
1c0082ca:	10055533          	p.exthz	a0,a0
1c0082ce:	c7a71733          	p.extractu	a4,a4,3,26
1c0082d2:	053e                	slli	a0,a0,0xf
1c0082d4:	177d                	addi	a4,a4,-1
1c0082d6:	00e55433          	srl	s0,a0,a4
1c0082da:	c380                	sw	s0,0(a5)
1c0082dc:	1c0017b7          	lui	a5,0x1c001
1c0082e0:	c5078793          	addi	a5,a5,-944 # 1c000c50 <_edata>
1c0082e4:	4705                	li	a4,1
1c0082e6:	00e7c4a3          	p.sb	a4,s1(a5)
1c0082ea:	8522                	mv	a0,s0
1c0082ec:	40b2                	lw	ra,12(sp)
1c0082ee:	4422                	lw	s0,8(sp)
1c0082f0:	4492                	lw	s1,4(sp)
1c0082f2:	0141                	addi	sp,sp,16
1c0082f4:	8082                	ret
1c0082f6:	85a2                	mv	a1,s0
1c0082f8:	8526                	mv	a0,s1
1c0082fa:	3dcd                	jal	1c0081ec <pos_fll_set_freq>
1c0082fc:	b7c5                	j	1c0082dc <pos_fll_init+0x82>

1c0082fe <pos_fll_constructor>:
1c0082fe:	1c0016b7          	lui	a3,0x1c001
1c008302:	1c0017b7          	lui	a5,0x1c001
1c008306:	c5c68713          	addi	a4,a3,-932 # 1c000c5c <pos_fll_freq>
1c00830a:	c5078793          	addi	a5,a5,-944 # 1c000c50 <_edata>
1c00830e:	c406ae23          	sw	zero,-932(a3)
1c008312:	00072223          	sw	zero,4(a4)
1c008316:	00072423          	sw	zero,8(a4)
1c00831a:	00079023          	sh	zero,0(a5)
1c00831e:	00078123          	sb	zero,2(a5)
1c008322:	8082                	ret

1c008324 <pos_soc_init>:
1c008324:	1141                	addi	sp,sp,-16
1c008326:	c606                	sw	ra,12(sp)
1c008328:	c422                	sw	s0,8(sp)
1c00832a:	3fd1                	jal	1c0082fe <pos_fll_constructor>
1c00832c:	4501                	li	a0,0
1c00832e:	3735                	jal	1c00825a <pos_fll_init>
1c008330:	1c001437          	lui	s0,0x1c001
1c008334:	c6a42423          	sw	a0,-920(s0) # 1c000c68 <pos_freq_domains>
1c008338:	4505                	li	a0,1
1c00833a:	3705                	jal	1c00825a <pos_fll_init>
1c00833c:	c6840413          	addi	s0,s0,-920
1c008340:	c408                	sw	a0,8(s0)
1c008342:	4509                	li	a0,2
1c008344:	3f19                	jal	1c00825a <pos_fll_init>
1c008346:	c048                	sw	a0,4(s0)
1c008348:	40b2                	lw	ra,12(sp)
1c00834a:	4422                	lw	s0,8(sp)
1c00834c:	0141                	addi	sp,sp,16
1c00834e:	8082                	ret

1c008350 <pos_wait_forever>:
1c008350:	f14027f3          	csrr	a5,mhartid
1c008354:	477d                	li	a4,31
1c008356:	ca5797b3          	p.extractu	a5,a5,5,5
1c00835a:	00e78963          	beq	a5,a4,1c00836c <pos_wait_forever+0x1c>
1c00835e:	002047b7          	lui	a5,0x204
1c008362:	577d                	li	a4,-1
1c008364:	c3d8                	sw	a4,4(a5)
1c008366:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c00836a:	a001                	j	1c00836a <pos_wait_forever+0x1a>
1c00836c:	1a10a7b7          	lui	a5,0x1a10a
1c008370:	577d                	li	a4,-1
1c008372:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c008376:	10500073          	wfi
1c00837a:	10500073          	wfi
1c00837e:	bfe5                	j	1c008376 <pos_wait_forever+0x26>

1c008380 <memcpy>:
1c008380:	00a5e7b3          	or	a5,a1,a0
1c008384:	fa27b7b3          	p.bclr	a5,a5,29,2
1c008388:	872a                	mv	a4,a0
1c00838a:	cb89                	beqz	a5,1c00839c <memcpy+0x1c>
1c00838c:	c61d                	beqz	a2,1c0083ba <memcpy+0x3a>
1c00838e:	004640fb          	lp.setup	x1,a2,1c008396 <memcpy+0x16>
1c008392:	0015c78b          	p.lbu	a5,1(a1!) # 1a100001 <__l2_shared_end+0xa0ffff9>
1c008396:	00f700ab          	p.sb	a5,1(a4!)
1c00839a:	8082                	ret
1c00839c:	fa2637b3          	p.bclr	a5,a2,29,2
1c0083a0:	f7fd                	bnez	a5,1c00838e <memcpy+0xe>
1c0083a2:	de65                	beqz	a2,1c00839a <memcpy+0x1a>
1c0083a4:	1671                	addi	a2,a2,-4
1c0083a6:	00265793          	srli	a5,a2,0x2
1c0083aa:	0785                	addi	a5,a5,1
1c0083ac:	0047c0fb          	lp.setup	x1,a5,1c0083b4 <memcpy+0x34>
1c0083b0:	0045a68b          	p.lw	a3,4(a1!)
1c0083b4:	00d7222b          	p.sw	a3,4(a4!)
1c0083b8:	8082                	ret
1c0083ba:	8082                	ret

1c0083bc <memmove>:
1c0083bc:	40b507b3          	sub	a5,a0,a1
1c0083c0:	00c7eb63          	bltu	a5,a2,1c0083d6 <memmove+0x1a>
1c0083c4:	87aa                	mv	a5,a0
1c0083c6:	c605                	beqz	a2,1c0083ee <memmove+0x32>
1c0083c8:	004640fb          	lp.setup	x1,a2,1c0083d0 <memmove+0x14>
1c0083cc:	0015c70b          	p.lbu	a4,1(a1!)
1c0083d0:	00e780ab          	p.sb	a4,1(a5!)
1c0083d4:	8082                	ret
1c0083d6:	167d                	addi	a2,a2,-1
1c0083d8:	00c507b3          	add	a5,a0,a2
1c0083dc:	95b2                	add	a1,a1,a2
1c0083de:	0605                	addi	a2,a2,1
1c0083e0:	004640fb          	lp.setup	x1,a2,1c0083e8 <memmove+0x2c>
1c0083e4:	fff5c70b          	p.lbu	a4,-1(a1!)
1c0083e8:	fee78fab          	p.sb	a4,-1(a5!)
1c0083ec:	8082                	ret
1c0083ee:	8082                	ret

1c0083f0 <strchr>:
1c0083f0:	00054783          	lbu	a5,0(a0)
1c0083f4:	0ff5f593          	andi	a1,a1,255
1c0083f8:	00b78c63          	beq	a5,a1,1c008410 <strchr+0x20>
1c0083fc:	cb99                	beqz	a5,1c008412 <strchr+0x22>
1c0083fe:	00150793          	addi	a5,a0,1
1c008402:	a011                	j	1c008406 <strchr+0x16>
1c008404:	c719                	beqz	a4,1c008412 <strchr+0x22>
1c008406:	853e                	mv	a0,a5
1c008408:	0017c70b          	p.lbu	a4,1(a5!)
1c00840c:	feb71ce3          	bne	a4,a1,1c008404 <strchr+0x14>
1c008410:	8082                	ret
1c008412:	0015b593          	seqz	a1,a1
1c008416:	40b005b3          	neg	a1,a1
1c00841a:	8d6d                	and	a0,a0,a1
1c00841c:	8082                	ret

1c00841e <fputc>:
1c00841e:	6689                	lui	a3,0x2
1c008420:	f14027f3          	csrr	a5,mhartid
1c008424:	f8068693          	addi	a3,a3,-128 # 1f80 <__cluster_text_size+0x1f80>
1c008428:	00379713          	slli	a4,a5,0x3
1c00842c:	078a                	slli	a5,a5,0x2
1c00842e:	8ff5                	and	a5,a5,a3
1c008430:	ee873733          	p.bclr	a4,a4,23,8
1c008434:	1a10f6b7          	lui	a3,0x1a10f
1c008438:	0ff57513          	andi	a0,a0,255
1c00843c:	9736                	add	a4,a4,a3
1c00843e:	00a7e723          	p.sw	a0,a4(a5)
1c008442:	4501                	li	a0,0
1c008444:	8082                	ret

1c008446 <pos_libc_fputc_locked>:
1c008446:	bfe1                	j	1c00841e <fputc>

1c008448 <pos_libc_prf_locked>:
1c008448:	a07d                	j	1c0084f6 <pos_libc_prf>

1c00844a <exit>:
1c00844a:	1141                	addi	sp,sp,-16
1c00844c:	c606                	sw	ra,12(sp)
1c00844e:	1a1047b7          	lui	a5,0x1a104
1c008452:	c1f54533          	p.bset	a0,a0,0,31
1c008456:	0aa7a023          	sw	a0,160(a5) # 1a1040a0 <__l2_shared_end+0xa104098>
1c00845a:	3ddd                	jal	1c008350 <pos_wait_forever>

1c00845c <pos_io_start>:
1c00845c:	4501                	li	a0,0
1c00845e:	8082                	ret

1c008460 <pos_io_stop>:
1c008460:	4501                	li	a0,0
1c008462:	8082                	ret

1c008464 <printf>:
1c008464:	7139                	addi	sp,sp,-64
1c008466:	02410313          	addi	t1,sp,36
1c00846a:	d432                	sw	a2,40(sp)
1c00846c:	862a                	mv	a2,a0
1c00846e:	1c008537          	lui	a0,0x1c008
1c008472:	d22e                	sw	a1,36(sp)
1c008474:	d636                	sw	a3,44(sp)
1c008476:	4589                	li	a1,2
1c008478:	869a                	mv	a3,t1
1c00847a:	44650513          	addi	a0,a0,1094 # 1c008446 <pos_libc_fputc_locked>
1c00847e:	ce06                	sw	ra,28(sp)
1c008480:	d83a                	sw	a4,48(sp)
1c008482:	da3e                	sw	a5,52(sp)
1c008484:	dc42                	sw	a6,56(sp)
1c008486:	de46                	sw	a7,60(sp)
1c008488:	c61a                	sw	t1,12(sp)
1c00848a:	3f7d                	jal	1c008448 <pos_libc_prf_locked>
1c00848c:	40f2                	lw	ra,28(sp)
1c00848e:	6121                	addi	sp,sp,64
1c008490:	8082                	ret

1c008492 <pos_libc_to_x>:
1c008492:	872a                	mv	a4,a0
1c008494:	87aa                	mv	a5,a0
1c008496:	4325                	li	t1,9
1c008498:	02c5f8b3          	remu	a7,a1,a2
1c00849c:	4501                	li	a0,0
1c00849e:	0ff8f813          	andi	a6,a7,255
1c0084a2:	02c5d5b3          	divu	a1,a1,a2
1c0084a6:	03080813          	addi	a6,a6,48
1c0084aa:	01137463          	bleu	a7,t1,1c0084b2 <pos_libc_to_x+0x20>
1c0084ae:	02700513          	li	a0,39
1c0084b2:	9542                	add	a0,a0,a6
1c0084b4:	00a780ab          	p.sb	a0,1(a5!)
1c0084b8:	f1e5                	bnez	a1,1c008498 <pos_libc_to_x+0x6>
1c0084ba:	40e78533          	sub	a0,a5,a4
1c0084be:	00d55d63          	ble	a3,a0,1c0084d8 <pos_libc_to_x+0x46>
1c0084c2:	40f70633          	sub	a2,a4,a5
1c0084c6:	03000593          	li	a1,48
1c0084ca:	96b2                	add	a3,a3,a2
1c0084cc:	0046c0fb          	lp.setup	x1,a3,1c0084d4 <pos_libc_to_x+0x42>
1c0084d0:	00b780ab          	p.sb	a1,1(a5!)
1c0084d4:	40e78533          	sub	a0,a5,a4
1c0084d8:	fe078fab          	p.sb	zero,-1(a5!)
1c0084dc:	00f77c63          	bleu	a5,a4,1c0084f4 <pos_libc_to_x+0x62>
1c0084e0:	00074603          	lbu	a2,0(a4)
1c0084e4:	0007c683          	lbu	a3,0(a5)
1c0084e8:	fec78fab          	p.sb	a2,-1(a5!)
1c0084ec:	00d700ab          	p.sb	a3,1(a4!)
1c0084f0:	fef768e3          	bltu	a4,a5,1c0084e0 <pos_libc_to_x+0x4e>
1c0084f4:	8082                	ret

1c0084f6 <pos_libc_prf>:
1c0084f6:	7169                	addi	sp,sp,-304
1c0084f8:	12812423          	sw	s0,296(sp)
1c0084fc:	12912223          	sw	s1,292(sp)
1c008500:	11712623          	sw	s7,268(sp)
1c008504:	11812423          	sw	s8,264(sp)
1c008508:	11912223          	sw	s9,260(sp)
1c00850c:	11a12023          	sw	s10,256(sp)
1c008510:	dfee                	sw	s11,252(sp)
1c008512:	12112623          	sw	ra,300(sp)
1c008516:	13212023          	sw	s2,288(sp)
1c00851a:	11312e23          	sw	s3,284(sp)
1c00851e:	11412c23          	sw	s4,280(sp)
1c008522:	11512a23          	sw	s5,276(sp)
1c008526:	11612823          	sw	s6,272(sp)
1c00852a:	8caa                	mv	s9,a0
1c00852c:	8bae                	mv	s7,a1
1c00852e:	84b2                	mv	s1,a2
1c008530:	8c36                	mv	s8,a3
1c008532:	4401                	li	s0,0
1c008534:	1c000db7          	lui	s11,0x1c000
1c008538:	02410d13          	addi	s10,sp,36
1c00853c:	0004c503          	lbu	a0,0(s1) # 1c092000 <__cluster_text_end+0x82000>
1c008540:	0485                	addi	s1,s1,1
1c008542:	cd11                	beqz	a0,1c00855e <pos_libc_prf+0x68>
1c008544:	02500793          	li	a5,37
1c008548:	04f50763          	beq	a0,a5,1c008596 <pos_libc_prf+0xa0>
1c00854c:	85de                	mv	a1,s7
1c00854e:	9c82                	jalr	s9
1c008550:	15f52c63          	p.beqimm	a0,-1,1c0086a8 <pos_libc_prf+0x1b2>
1c008554:	0405                	addi	s0,s0,1
1c008556:	0004c503          	lbu	a0,0(s1)
1c00855a:	0485                	addi	s1,s1,1
1c00855c:	f565                	bnez	a0,1c008544 <pos_libc_prf+0x4e>
1c00855e:	8522                	mv	a0,s0
1c008560:	12c12083          	lw	ra,300(sp)
1c008564:	12812403          	lw	s0,296(sp)
1c008568:	12412483          	lw	s1,292(sp)
1c00856c:	12012903          	lw	s2,288(sp)
1c008570:	11c12983          	lw	s3,284(sp)
1c008574:	11812a03          	lw	s4,280(sp)
1c008578:	11412a83          	lw	s5,276(sp)
1c00857c:	11012b03          	lw	s6,272(sp)
1c008580:	10c12b83          	lw	s7,268(sp)
1c008584:	10812c03          	lw	s8,264(sp)
1c008588:	10412c83          	lw	s9,260(sp)
1c00858c:	10012d03          	lw	s10,256(sp)
1c008590:	5dfe                	lw	s11,252(sp)
1c008592:	6155                	addi	sp,sp,304
1c008594:	8082                	ret
1c008596:	0004cb03          	lbu	s6,0(s1)
1c00859a:	02000813          	li	a6,32
1c00859e:	00148a93          	addi	s5,s1,1
1c0085a2:	034d8513          	addi	a0,s11,52 # 1c000034 <__DTOR_END__+0x18>
1c0085a6:	85da                	mv	a1,s6
1c0085a8:	c842                	sw	a6,16(sp)
1c0085aa:	cc02                	sw	zero,24(sp)
1c0085ac:	ca02                	sw	zero,20(sp)
1c0085ae:	ce02                	sw	zero,28(sp)
1c0085b0:	c602                	sw	zero,12(sp)
1c0085b2:	02300913          	li	s2,35
1c0085b6:	02d00a13          	li	s4,45
1c0085ba:	89d6                	mv	s3,s5
1c0085bc:	3d15                	jal	1c0083f0 <strchr>
1c0085be:	c915                	beqz	a0,1c0085f2 <pos_libc_prf+0xfc>
1c0085c0:	112b0d63          	beq	s6,s2,1c0086da <pos_libc_prf+0x1e4>
1c0085c4:	0f697463          	bleu	s6,s2,1c0086ac <pos_libc_prf+0x1b6>
1c0085c8:	114b0563          	beq	s6,s4,1c0086d2 <pos_libc_prf+0x1dc>
1c0085cc:	03000613          	li	a2,48
1c0085d0:	0ecb0c63          	beq	s6,a2,1c0086c8 <pos_libc_prf+0x1d2>
1c0085d4:	02b00693          	li	a3,43
1c0085d8:	0edb0463          	beq	s6,a3,1c0086c0 <pos_libc_prf+0x1ca>
1c0085dc:	84d6                	mv	s1,s5
1c0085de:	0004cb03          	lbu	s6,0(s1)
1c0085e2:	00148a93          	addi	s5,s1,1
1c0085e6:	034d8513          	addi	a0,s11,52
1c0085ea:	85da                	mv	a1,s6
1c0085ec:	89d6                	mv	s3,s5
1c0085ee:	3509                	jal	1c0083f0 <strchr>
1c0085f0:	f961                	bnez	a0,1c0085c0 <pos_libc_prf+0xca>
1c0085f2:	02a00613          	li	a2,42
1c0085f6:	10cb0863          	beq	s6,a2,1c008706 <pos_libc_prf+0x210>
1c0085fa:	fd0b0613          	addi	a2,s6,-48
1c0085fe:	45a5                	li	a1,9
1c008600:	4a01                	li	s4,0
1c008602:	0ec5f263          	bleu	a2,a1,1c0086e6 <pos_libc_prf+0x1f0>
1c008606:	02e00713          	li	a4,46
1c00860a:	5afd                	li	s5,-1
1c00860c:	14eb0563          	beq	s6,a4,1c008756 <pos_libc_prf+0x260>
1c008610:	1c0007b7          	lui	a5,0x1c000
1c008614:	85da                	mv	a1,s6
1c008616:	03c78513          	addi	a0,a5,60 # 1c00003c <__DTOR_END__+0x20>
1c00861a:	3bd9                	jal	1c0083f0 <strchr>
1c00861c:	84ce                	mv	s1,s3
1c00861e:	c509                	beqz	a0,1c008628 <pos_libc_prf+0x132>
1c008620:	0009cb03          	lbu	s6,0(s3) # 1c092000 <__cluster_text_end+0x82000>
1c008624:	00198493          	addi	s1,s3,1
1c008628:	06700713          	li	a4,103
1c00862c:	0f675b63          	ble	s6,a4,1c008722 <pos_libc_prf+0x22c>
1c008630:	07000713          	li	a4,112
1c008634:	72eb0963          	beq	s6,a4,1c008d66 <pos_libc_prf+0x870>
1c008638:	15675363          	ble	s6,a4,1c00877e <pos_libc_prf+0x288>
1c00863c:	07500713          	li	a4,117
1c008640:	6eeb0863          	beq	s6,a4,1c008d30 <pos_libc_prf+0x83a>
1c008644:	07800713          	li	a4,120
1c008648:	5ceb0a63          	beq	s6,a4,1c008c1c <pos_libc_prf+0x726>
1c00864c:	07300713          	li	a4,115
1c008650:	70eb1463          	bne	s6,a4,1c008d58 <pos_libc_prf+0x862>
1c008654:	000c2583          	lw	a1,0(s8)
1c008658:	004c0913          	addi	s2,s8,4
1c00865c:	4981                	li	s3,0
1c00865e:	872e                	mv	a4,a1
1c008660:	0c8350fb          	lp.setupi	x1,200,1c00866c <pos_libc_prf+0x176>
1c008664:	0017468b          	p.lbu	a3,1(a4!)
1c008668:	74068063          	beqz	a3,1c008da8 <pos_libc_prf+0x8b2>
1c00866c:	0985                	addi	s3,s3,1
1c00866e:	000ac763          	bltz	s5,1c00867c <pos_libc_prf+0x186>
1c008672:	0559c9b3          	p.min	s3,s3,s5
1c008676:	8c4a                	mv	s8,s2
1c008678:	ec0982e3          	beqz	s3,1c00853c <pos_libc_prf+0x46>
1c00867c:	864e                	mv	a2,s3
1c00867e:	856a                	mv	a0,s10
1c008680:	3301                	jal	1c008380 <memcpy>
1c008682:	8c4a                	mv	s8,s2
1c008684:	5f49c063          	blt	s3,s4,1c008c64 <pos_libc_prf+0x76e>
1c008688:	8a4e                	mv	s4,s3
1c00868a:	896a                	mv	s2,s10
1c00868c:	41a409b3          	sub	s3,s0,s10
1c008690:	a029                	j	1c00869a <pos_libc_prf+0x1a4>
1c008692:	01298433          	add	s0,s3,s2
1c008696:	ea0a03e3          	beqz	s4,1c00853c <pos_libc_prf+0x46>
1c00869a:	0019450b          	p.lbu	a0,1(s2!)
1c00869e:	85de                	mv	a1,s7
1c0086a0:	1a7d                	addi	s4,s4,-1
1c0086a2:	9c82                	jalr	s9
1c0086a4:	fff537e3          	p.bneimm	a0,-1,1c008692 <pos_libc_prf+0x19c>
1c0086a8:	547d                	li	s0,-1
1c0086aa:	bd55                	j	1c00855e <pos_libc_prf+0x68>
1c0086ac:	ea0b09e3          	beqz	s6,1c00855e <pos_libc_prf+0x68>
1c0086b0:	02000513          	li	a0,32
1c0086b4:	f2ab14e3          	bne	s6,a0,1c0085dc <pos_libc_prf+0xe6>
1c0086b8:	4785                	li	a5,1
1c0086ba:	cc3e                	sw	a5,24(sp)
1c0086bc:	84d6                	mv	s1,s5
1c0086be:	b705                	j	1c0085de <pos_libc_prf+0xe8>
1c0086c0:	4705                	li	a4,1
1c0086c2:	ca3a                	sw	a4,20(sp)
1c0086c4:	84d6                	mv	s1,s5
1c0086c6:	bf21                	j	1c0085de <pos_libc_prf+0xe8>
1c0086c8:	03000713          	li	a4,48
1c0086cc:	c83a                	sw	a4,16(sp)
1c0086ce:	84d6                	mv	s1,s5
1c0086d0:	b739                	j	1c0085de <pos_libc_prf+0xe8>
1c0086d2:	4785                	li	a5,1
1c0086d4:	ce3e                	sw	a5,28(sp)
1c0086d6:	84d6                	mv	s1,s5
1c0086d8:	b719                	j	1c0085de <pos_libc_prf+0xe8>
1c0086da:	4805                	li	a6,1
1c0086dc:	c642                	sw	a6,12(sp)
1c0086de:	84d6                	mv	s1,s5
1c0086e0:	bdfd                	j	1c0085de <pos_libc_prf+0xe8>
1c0086e2:	84d6                	mv	s1,s5
1c0086e4:	0a85                	addi	s5,s5,1
1c0086e6:	002a1793          	slli	a5,s4,0x2
1c0086ea:	97d2                	add	a5,a5,s4
1c0086ec:	0786                	slli	a5,a5,0x1
1c0086ee:	97da                	add	a5,a5,s6
1c0086f0:	000acb03          	lbu	s6,0(s5)
1c0086f4:	fd078a13          	addi	s4,a5,-48
1c0086f8:	fd0b0793          	addi	a5,s6,-48
1c0086fc:	fef5f3e3          	bleu	a5,a1,1c0086e2 <pos_libc_prf+0x1ec>
1c008700:	00248993          	addi	s3,s1,2
1c008704:	a811                	j	1c008718 <pos_libc_prf+0x222>
1c008706:	000c2a03          	lw	s4,0(s8)
1c00870a:	0c11                	addi	s8,s8,4
1c00870c:	0e0a4063          	bltz	s4,1c0087ec <pos_libc_prf+0x2f6>
1c008710:	000acb03          	lbu	s6,0(s5)
1c008714:	00248993          	addi	s3,s1,2
1c008718:	0c800713          	li	a4,200
1c00871c:	04ea5a33          	p.minu	s4,s4,a4
1c008720:	b5dd                	j	1c008606 <pos_libc_prf+0x110>
1c008722:	06500713          	li	a4,101
1c008726:	0ceb5863          	ble	a4,s6,1c0087f6 <pos_libc_prf+0x300>
1c00872a:	04700713          	li	a4,71
1c00872e:	4d674d63          	blt	a4,s6,1c008c08 <pos_libc_prf+0x712>
1c008732:	04500713          	li	a4,69
1c008736:	0ceb5063          	ble	a4,s6,1c0087f6 <pos_libc_prf+0x300>
1c00873a:	e20b02e3          	beqz	s6,1c00855e <pos_libc_prf+0x68>
1c00873e:	02500713          	li	a4,37
1c008742:	60eb1b63          	bne	s6,a4,1c008d58 <pos_libc_prf+0x862>
1c008746:	85de                	mv	a1,s7
1c008748:	02500513          	li	a0,37
1c00874c:	9c82                	jalr	s9
1c00874e:	f5f52de3          	p.beqimm	a0,-1,1c0086a8 <pos_libc_prf+0x1b2>
1c008752:	0405                	addi	s0,s0,1
1c008754:	b509                	j	1c008556 <pos_libc_prf+0x60>
1c008756:	0009c783          	lbu	a5,0(s3)
1c00875a:	02a00713          	li	a4,42
1c00875e:	00198593          	addi	a1,s3,1
1c008762:	04e79c63          	bne	a5,a4,1c0087ba <pos_libc_prf+0x2c4>
1c008766:	000c2a83          	lw	s5,0(s8)
1c00876a:	0019cb03          	lbu	s6,1(s3)
1c00876e:	0c11                	addi	s8,s8,4
1c008770:	0989                	addi	s3,s3,2
1c008772:	0c800713          	li	a4,200
1c008776:	e9575de3          	ble	s5,a4,1c008610 <pos_libc_prf+0x11a>
1c00877a:	5afd                	li	s5,-1
1c00877c:	bd51                	j	1c008610 <pos_libc_prf+0x11a>
1c00877e:	06e00713          	li	a4,110
1c008782:	60eb0d63          	beq	s6,a4,1c008d9c <pos_libc_prf+0x8a6>
1c008786:	55675263          	ble	s6,a4,1c008cca <pos_libc_prf+0x7d4>
1c00878a:	4832                	lw	a6,12(sp)
1c00878c:	004c0913          	addi	s2,s8,4
1c008790:	000c2583          	lw	a1,0(s8)
1c008794:	6e080063          	beqz	a6,1c008e74 <pos_libc_prf+0x97e>
1c008798:	03000793          	li	a5,48
1c00879c:	02f10223          	sb	a5,36(sp)
1c0087a0:	6a059063          	bnez	a1,1c008e40 <pos_libc_prf+0x94a>
1c0087a4:	020102a3          	sb	zero,37(sp)
1c0087a8:	8c4a                	mv	s8,s2
1c0087aa:	89c2                	mv	s3,a6
1c0087ac:	edfaace3          	p.beqimm	s5,-1,1c008684 <pos_libc_prf+0x18e>
1c0087b0:	02000813          	li	a6,32
1c0087b4:	49b2                	lw	s3,12(sp)
1c0087b6:	c842                	sw	a6,16(sp)
1c0087b8:	b5f1                	j	1c008684 <pos_libc_prf+0x18e>
1c0087ba:	fd078513          	addi	a0,a5,-48
1c0087be:	4725                	li	a4,9
1c0087c0:	8b3e                	mv	s6,a5
1c0087c2:	86ae                	mv	a3,a1
1c0087c4:	4a81                	li	s5,0
1c0087c6:	4625                	li	a2,9
1c0087c8:	89ae                	mv	s3,a1
1c0087ca:	e4a763e3          	bltu	a4,a0,1c008610 <pos_libc_prf+0x11a>
1c0087ce:	002a9793          	slli	a5,s5,0x2
1c0087d2:	97d6                	add	a5,a5,s5
1c0087d4:	0786                	slli	a5,a5,0x1
1c0087d6:	97da                	add	a5,a5,s6
1c0087d8:	0016cb0b          	p.lbu	s6,1(a3!) # 1a10f001 <__l2_shared_end+0xa10eff9>
1c0087dc:	fd078a93          	addi	s5,a5,-48
1c0087e0:	fd0b0793          	addi	a5,s6,-48
1c0087e4:	fef675e3          	bleu	a5,a2,1c0087ce <pos_libc_prf+0x2d8>
1c0087e8:	89b6                	mv	s3,a3
1c0087ea:	b761                	j	1c008772 <pos_libc_prf+0x27c>
1c0087ec:	4705                	li	a4,1
1c0087ee:	41400a33          	neg	s4,s4
1c0087f2:	ce3a                	sw	a4,28(sp)
1c0087f4:	bf31                	j	1c008710 <pos_libc_prf+0x21a>
1c0087f6:	0c1d                	addi	s8,s8,7
1c0087f8:	c40c3c33          	p.bclr	s8,s8,2,0
1c0087fc:	000c2683          	lw	a3,0(s8)
1c008800:	004c2503          	lw	a0,4(s8)
1c008804:	7ff00713          	li	a4,2047
1c008808:	0156d593          	srli	a1,a3,0x15
1c00880c:	01455813          	srli	a6,a0,0x14
1c008810:	00b51613          	slli	a2,a0,0xb
1c008814:	8e4d                	or	a2,a2,a1
1c008816:	e8b83833          	p.bclr	a6,a6,20,11
1c00881a:	0c21                	addi	s8,s8,8
1c00881c:	06ae                	slli	a3,a3,0xb
1c00881e:	c1f63633          	p.bclr	a2,a2,0,31
1c008822:	64e80b63          	beq	a6,a4,1c008e78 <pos_libc_prf+0x982>
1c008826:	04600713          	li	a4,70
1c00882a:	00eb1463          	bne	s6,a4,1c008832 <pos_libc_prf+0x33c>
1c00882e:	06600b13          	li	s6,102
1c008832:	00d86733          	or	a4,a6,a3
1c008836:	8f51                	or	a4,a4,a2
1c008838:	66070b63          	beqz	a4,1c008eae <pos_libc_prf+0x9b8>
1c00883c:	c0280813          	addi	a6,a6,-1022
1c008840:	c1f645b3          	p.bset	a1,a2,0,31
1c008844:	060541e3          	bltz	a0,1c0090a6 <pos_libc_prf+0xbb0>
1c008848:	4752                	lw	a4,20(sp)
1c00884a:	040702e3          	beqz	a4,1c00908e <pos_libc_prf+0xb98>
1c00884e:	02b00713          	li	a4,43
1c008852:	02e10223          	sb	a4,36(sp)
1c008856:	02510f13          	addi	t5,sp,37
1c00885a:	5779                	li	a4,-2
1c00885c:	4301                	li	t1,0
1c00885e:	06e85763          	ble	a4,a6,1c0088cc <pos_libc_prf+0x3d6>
1c008862:	33333537          	lui	a0,0x33333
1c008866:	800008b7          	lui	a7,0x80000
1c00886a:	33250513          	addi	a0,a0,818 # 33333332 <__cluster_text_end+0x17323332>
1c00886e:	fff8c893          	not	a7,a7
1c008872:	5e79                	li	t3,-2
1c008874:	a011                	j	1c008878 <pos_libc_prf+0x382>
1c008876:	883e                	mv	a6,a5
1c008878:	01f59613          	slli	a2,a1,0x1f
1c00887c:	0016d713          	srli	a4,a3,0x1
1c008880:	fc16b7b3          	p.bclr	a5,a3,30,1
1c008884:	8f51                	or	a4,a4,a2
1c008886:	00e786b3          	add	a3,a5,a4
1c00888a:	00f6b7b3          	sltu	a5,a3,a5
1c00888e:	8185                	srli	a1,a1,0x1
1c008890:	95be                	add	a1,a1,a5
1c008892:	00180793          	addi	a5,a6,1
1c008896:	feb560e3          	bltu	a0,a1,1c008876 <pos_libc_prf+0x380>
1c00889a:	00269613          	slli	a2,a3,0x2
1c00889e:	01e6de93          	srli	t4,a3,0x1e
1c0088a2:	00259713          	slli	a4,a1,0x2
1c0088a6:	96b2                	add	a3,a3,a2
1c0088a8:	00eee733          	or	a4,t4,a4
1c0088ac:	95ba                	add	a1,a1,a4
1c0088ae:	00c6b633          	sltu	a2,a3,a2
1c0088b2:	95b2                	add	a1,a1,a2
1c0088b4:	01f6d713          	srli	a4,a3,0x1f
1c0088b8:	0809                	addi	a6,a6,2
1c0088ba:	137d                	addi	t1,t1,-1
1c0088bc:	01159663          	bne	a1,a7,1c0088c8 <pos_libc_prf+0x3d2>
1c0088c0:	0686                	slli	a3,a3,0x1
1c0088c2:	fc1745b3          	p.bset	a1,a4,30,1
1c0088c6:	883e                	mv	a6,a5
1c0088c8:	fbc848e3          	blt	a6,t3,1c008878 <pos_libc_prf+0x382>
1c0088cc:	07005563          	blez	a6,1c008936 <pos_libc_prf+0x440>
1c0088d0:	800008b7          	lui	a7,0x80000
1c0088d4:	4e15                	li	t3,5
1c0088d6:	fff8c893          	not	a7,a7
1c0088da:	00268613          	addi	a2,a3,2
1c0088de:	00d636b3          	sltu	a3,a2,a3
1c0088e2:	95b6                	add	a1,a1,a3
1c0088e4:	03c5d533          	divu	a0,a1,t3
1c0088e8:	00365793          	srli	a5,a2,0x3
1c0088ec:	187d                	addi	a6,a6,-1
1c0088ee:	0305                	addi	t1,t1,1
1c0088f0:	00251713          	slli	a4,a0,0x2
1c0088f4:	972a                	add	a4,a4,a0
1c0088f6:	8d99                	sub	a1,a1,a4
1c0088f8:	01d59713          	slli	a4,a1,0x1d
1c0088fc:	8fd9                	or	a5,a5,a4
1c0088fe:	03c7d7b3          	divu	a5,a5,t3
1c008902:	00379693          	slli	a3,a5,0x3
1c008906:	00579713          	slli	a4,a5,0x5
1c00890a:	9736                	add	a4,a4,a3
1c00890c:	40e60733          	sub	a4,a2,a4
1c008910:	03c75733          	divu	a4,a4,t3
1c008914:	01d7d593          	srli	a1,a5,0x1d
1c008918:	95aa                	add	a1,a1,a0
1c00891a:	96ba                	add	a3,a3,a4
1c00891c:	00e6b733          	sltu	a4,a3,a4
1c008920:	95ba                	add	a1,a1,a4
1c008922:	01f6d793          	srli	a5,a3,0x1f
1c008926:	0586                	slli	a1,a1,0x1
1c008928:	8ddd                	or	a1,a1,a5
1c00892a:	0686                	slli	a3,a3,0x1
1c00892c:	187d                	addi	a6,a6,-1
1c00892e:	feb8fae3          	bleu	a1,a7,1c008922 <pos_libc_prf+0x42c>
1c008932:	fb0044e3          	bgtz	a6,1c0088da <pos_libc_prf+0x3e4>
1c008936:	4711                	li	a4,4
1c008938:	41070833          	sub	a6,a4,a6
1c00893c:	011840fb          	lp.setup	x1,a6,1c00895e <pos_libc_prf+0x468>
1c008940:	01f59713          	slli	a4,a1,0x1f
1c008944:	0016d793          	srli	a5,a3,0x1
1c008948:	8fd9                	or	a5,a5,a4
1c00894a:	fc16b6b3          	p.bclr	a3,a3,30,1
1c00894e:	00f68e33          	add	t3,a3,a5
1c008952:	8185                	srli	a1,a1,0x1
1c008954:	00de36b3          	sltu	a3,t3,a3
1c008958:	00b68733          	add	a4,a3,a1
1c00895c:	85ba                	mv	a1,a4
1c00895e:	86f2                	mv	a3,t3
1c008960:	06700693          	li	a3,103
1c008964:	580acb63          	bltz	s5,1c008efa <pos_libc_prf+0xa04>
1c008968:	4adb0563          	beq	s6,a3,1c008e12 <pos_libc_prf+0x91c>
1c00896c:	04700693          	li	a3,71
1c008970:	4adb0163          	beq	s6,a3,1c008e12 <pos_libc_prf+0x91c>
1c008974:	06600693          	li	a3,102
1c008978:	64db0d63          	beq	s6,a3,1c008fd2 <pos_libc_prf+0xadc>
1c00897c:	001a8e93          	addi	t4,s5,1
1c008980:	4541                	li	a0,16
1c008982:	04aeceb3          	p.min	t4,t4,a0
1c008986:	1efd                	addi	t4,t4,-1
1c008988:	4281                	li	t0,0
1c00898a:	001f0893          	addi	a7,t5,1
1c00898e:	4601                	li	a2,0
1c008990:	080006b7          	lui	a3,0x8000
1c008994:	4f95                	li	t6,5
1c008996:	0e85                	addi	t4,t4,1
1c008998:	02eec0fb          	lp.setup	x1,t4,1c0089f4 <pos_libc_prf+0x4fe>
1c00899c:	00260593          	addi	a1,a2,2
1c0089a0:	00c5b7b3          	sltu	a5,a1,a2
1c0089a4:	97b6                	add	a5,a5,a3
1c0089a6:	03f7d533          	divu	a0,a5,t6
1c0089aa:	0035d693          	srli	a3,a1,0x3
1c0089ae:	00251613          	slli	a2,a0,0x2
1c0089b2:	962a                	add	a2,a2,a0
1c0089b4:	8f91                	sub	a5,a5,a2
1c0089b6:	07f6                	slli	a5,a5,0x1d
1c0089b8:	8edd                	or	a3,a3,a5
1c0089ba:	03f6d6b3          	divu	a3,a3,t6
1c0089be:	00369613          	slli	a2,a3,0x3
1c0089c2:	00569793          	slli	a5,a3,0x5
1c0089c6:	97b2                	add	a5,a5,a2
1c0089c8:	40f587b3          	sub	a5,a1,a5
1c0089cc:	03f7d7b3          	divu	a5,a5,t6
1c0089d0:	82f5                	srli	a3,a3,0x1d
1c0089d2:	96aa                	add	a3,a3,a0
1c0089d4:	963e                	add	a2,a2,a5
1c0089d6:	00f637b3          	sltu	a5,a2,a5
1c0089da:	96be                	add	a3,a3,a5
1c0089dc:	01f69513          	slli	a0,a3,0x1f
1c0089e0:	00165793          	srli	a5,a2,0x1
1c0089e4:	fc1635b3          	p.bclr	a1,a2,30,1
1c0089e8:	8fc9                	or	a5,a5,a0
1c0089ea:	00f58633          	add	a2,a1,a5
1c0089ee:	8285                	srli	a3,a3,0x1
1c0089f0:	00b637b3          	sltu	a5,a2,a1
1c0089f4:	96be                	add	a3,a3,a5
1c0089f6:	9672                	add	a2,a2,t3
1c0089f8:	01c63e33          	sltu	t3,a2,t3
1c0089fc:	9736                	add	a4,a4,a3
1c0089fe:	9772                	add	a4,a4,t3
1c008a00:	f60736b3          	p.bclr	a3,a4,27,0
1c008a04:	8e32                	mv	t3,a2
1c008a06:	c2ad                	beqz	a3,1c008a68 <pos_libc_prf+0x572>
1c008a08:	002e0693          	addi	a3,t3,2
1c008a0c:	01c6be33          	sltu	t3,a3,t3
1c008a10:	9772                	add	a4,a4,t3
1c008a12:	4815                	li	a6,5
1c008a14:	03075533          	divu	a0,a4,a6
1c008a18:	0036d593          	srli	a1,a3,0x3
1c008a1c:	0305                	addi	t1,t1,1
1c008a1e:	00251613          	slli	a2,a0,0x2
1c008a22:	962a                	add	a2,a2,a0
1c008a24:	8f11                	sub	a4,a4,a2
1c008a26:	0776                	slli	a4,a4,0x1d
1c008a28:	8dd9                	or	a1,a1,a4
1c008a2a:	0305d5b3          	divu	a1,a1,a6
1c008a2e:	00359613          	slli	a2,a1,0x3
1c008a32:	00559713          	slli	a4,a1,0x5
1c008a36:	9732                	add	a4,a4,a2
1c008a38:	40e68733          	sub	a4,a3,a4
1c008a3c:	03075733          	divu	a4,a4,a6
1c008a40:	81f5                	srli	a1,a1,0x1d
1c008a42:	952e                	add	a0,a0,a1
1c008a44:	00c706b3          	add	a3,a4,a2
1c008a48:	00e6b733          	sltu	a4,a3,a4
1c008a4c:	972a                	add	a4,a4,a0
1c008a4e:	01f71593          	slli	a1,a4,0x1f
1c008a52:	0016d613          	srli	a2,a3,0x1
1c008a56:	8e4d                	or	a2,a2,a1
1c008a58:	fc16b6b3          	p.bclr	a3,a3,30,1
1c008a5c:	00c68e33          	add	t3,a3,a2
1c008a60:	8305                	srli	a4,a4,0x1
1c008a62:	00de36b3          	sltu	a3,t3,a3
1c008a66:	9736                	add	a4,a4,a3
1c008a68:	06600693          	li	a3,102
1c008a6c:	4cdb0463          	beq	s6,a3,1c008f34 <pos_libc_prf+0xa3e>
1c008a70:	002e1693          	slli	a3,t3,0x2
1c008a74:	01ee5593          	srli	a1,t3,0x1e
1c008a78:	00271613          	slli	a2,a4,0x2
1c008a7c:	9e36                	add	t3,t3,a3
1c008a7e:	8e4d                	or	a2,a2,a1
1c008a80:	9732                	add	a4,a4,a2
1c008a82:	00de35b3          	sltu	a1,t3,a3
1c008a86:	95ba                	add	a1,a1,a4
1c008a88:	0586                	slli	a1,a1,0x1
1c008a8a:	01fe5713          	srli	a4,t3,0x1f
1c008a8e:	8dd9                	or	a1,a1,a4
1c008a90:	01c5d713          	srli	a4,a1,0x1c
1c008a94:	03070613          	addi	a2,a4,48
1c008a98:	47b2                	lw	a5,12(sp)
1c008a9a:	10000537          	lui	a0,0x10000
1c008a9e:	00e036b3          	snez	a3,a4
1c008aa2:	157d                	addi	a0,a0,-1
1c008aa4:	00cf0023          	sb	a2,0(t5)
1c008aa8:	001e1713          	slli	a4,t3,0x1
1c008aac:	8de9                	and	a1,a1,a0
1c008aae:	40d30333          	sub	t1,t1,a3
1c008ab2:	46078863          	beqz	a5,1c008f22 <pos_libc_prf+0xa2c>
1c008ab6:	02e00693          	li	a3,46
1c008aba:	00df00a3          	sb	a3,1(t5)
1c008abe:	002f0893          	addi	a7,t5,2
1c008ac2:	040a8d63          	beqz	s5,1c008b1c <pos_libc_prf+0x626>
1c008ac6:	9ac6                	add	s5,s5,a7
1c008ac8:	4e3d                	li	t3,15
1c008aca:	411a8533          	sub	a0,s5,a7
1c008ace:	025540fb          	lp.setup	x1,a0,1c008b18 <pos_libc_prf+0x622>
1c008ad2:	00271793          	slli	a5,a4,0x2
1c008ad6:	01e75613          	srli	a2,a4,0x1e
1c008ada:	00259693          	slli	a3,a1,0x2
1c008ade:	00e78833          	add	a6,a5,a4
1c008ae2:	8ed1                	or	a3,a3,a2
1c008ae4:	96ae                	add	a3,a3,a1
1c008ae6:	00f837b3          	sltu	a5,a6,a5
1c008aea:	97b6                	add	a5,a5,a3
1c008aec:	0786                	slli	a5,a5,0x1
1c008aee:	01f85693          	srli	a3,a6,0x1f
1c008af2:	8fd5                	or	a5,a5,a3
1c008af4:	01c7d613          	srli	a2,a5,0x1c
1c008af8:	03000693          	li	a3,48
1c008afc:	01c05c63          	blez	t3,1c008b14 <pos_libc_prf+0x61e>
1c008b00:	00181713          	slli	a4,a6,0x1
1c008b04:	10000837          	lui	a6,0x10000
1c008b08:	187d                	addi	a6,a6,-1
1c008b0a:	03060693          	addi	a3,a2,48
1c008b0e:	1e7d                	addi	t3,t3,-1
1c008b10:	0107f5b3          	and	a1,a5,a6
1c008b14:	00d880ab          	p.sb	a3,1(a7!) # 80000001 <pulp__FC+0x80000002>
1c008b18:	0001                	nop
1c008b1a:	88d6                	mv	a7,s5
1c008b1c:	0c029663          	bnez	t0,1c008be8 <pos_libc_prf+0x6f2>
1c008b20:	c05b3733          	p.bclr	a4,s6,0,5
1c008b24:	04500693          	li	a3,69
1c008b28:	02d71963          	bne	a4,a3,1c008b5a <pos_libc_prf+0x664>
1c008b2c:	87da                	mv	a5,s6
1c008b2e:	00f88023          	sb	a5,0(a7)
1c008b32:	48034963          	bltz	t1,1c008fc4 <pos_libc_prf+0xace>
1c008b36:	02b00793          	li	a5,43
1c008b3a:	00f880a3          	sb	a5,1(a7)
1c008b3e:	47a9                	li	a5,10
1c008b40:	02f34733          	div	a4,t1,a5
1c008b44:	0891                	addi	a7,a7,4
1c008b46:	02f367b3          	rem	a5,t1,a5
1c008b4a:	03070713          	addi	a4,a4,48
1c008b4e:	fee88f23          	sb	a4,-2(a7)
1c008b52:	03078793          	addi	a5,a5,48
1c008b56:	fef88fa3          	sb	a5,-1(a7)
1c008b5a:	00088023          	sb	zero,0(a7)
1c008b5e:	41a889b3          	sub	s3,a7,s10
1c008b62:	4752                	lw	a4,20(sp)
1c008b64:	47e2                	lw	a5,24(sp)
1c008b66:	8f5d                	or	a4,a4,a5
1c008b68:	c63a                	sw	a4,12(sp)
1c008b6a:	24071663          	bnez	a4,1c008db6 <pos_libc_prf+0x8c0>
1c008b6e:	02414703          	lbu	a4,36(sp)
1c008b72:	02d00793          	li	a5,45
1c008b76:	24f70063          	beq	a4,a5,1c008db6 <pos_libc_prf+0x8c0>
1c008b7a:	0c800793          	li	a5,200
1c008b7e:	b337c5e3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008b82:	0f49c263          	blt	s3,s4,1c008c66 <pos_libc_prf+0x770>
1c008b86:	8a4e                	mv	s4,s3
1c008b88:	b00a11e3          	bnez	s4,1c00868a <pos_libc_prf+0x194>
1c008b8c:	ba45                	j	1c00853c <pos_libc_prf+0x46>
1c008b8e:	0605                	addi	a2,a2,1
1c008b90:	002e1793          	slli	a5,t3,0x2
1c008b94:	01ee5e93          	srli	t4,t3,0x1e
1c008b98:	00271693          	slli	a3,a4,0x2
1c008b9c:	01c78833          	add	a6,a5,t3
1c008ba0:	00dee6b3          	or	a3,t4,a3
1c008ba4:	96ba                	add	a3,a3,a4
1c008ba6:	00f837b3          	sltu	a5,a6,a5
1c008baa:	97b6                	add	a5,a5,a3
1c008bac:	0786                	slli	a5,a5,0x1
1c008bae:	01f85693          	srli	a3,a6,0x1f
1c008bb2:	8fd5                	or	a5,a5,a3
1c008bb4:	01c7de93          	srli	t4,a5,0x1c
1c008bb8:	03000693          	li	a3,48
1c008bbc:	00b05c63          	blez	a1,1c008bd4 <pos_libc_prf+0x6de>
1c008bc0:	00181e13          	slli	t3,a6,0x1
1c008bc4:	10000837          	lui	a6,0x10000
1c008bc8:	187d                	addi	a6,a6,-1
1c008bca:	030e8693          	addi	a3,t4,48
1c008bce:	15fd                	addi	a1,a1,-1
1c008bd0:	0107f733          	and	a4,a5,a6
1c008bd4:	fed60fa3          	sb	a3,-1(a2)
1c008bd8:	fac89be3          	bne	a7,a2,1c008b8e <pos_libc_prf+0x698>
1c008bdc:	015508b3          	add	a7,a0,s5
1c008be0:	f6028de3          	beqz	t0,1c008b5a <pos_libc_prf+0x664>
1c008be4:	06600b13          	li	s6,102
1c008be8:	03000613          	li	a2,48
1c008bec:	a011                	j	1c008bf0 <pos_libc_prf+0x6fa>
1c008bee:	88ba                	mv	a7,a4
1c008bf0:	fff88713          	addi	a4,a7,-1
1c008bf4:	00074683          	lbu	a3,0(a4)
1c008bf8:	fec68be3          	beq	a3,a2,1c008bee <pos_libc_prf+0x6f8>
1c008bfc:	02e00613          	li	a2,46
1c008c00:	f2c690e3          	bne	a3,a2,1c008b20 <pos_libc_prf+0x62a>
1c008c04:	88ba                	mv	a7,a4
1c008c06:	bf29                	j	1c008b20 <pos_libc_prf+0x62a>
1c008c08:	06300713          	li	a4,99
1c008c0c:	10eb0963          	beq	s6,a4,1c008d1e <pos_libc_prf+0x828>
1c008c10:	0d674163          	blt	a4,s6,1c008cd2 <pos_libc_prf+0x7dc>
1c008c14:	05800713          	li	a4,88
1c008c18:	14eb1063          	bne	s6,a4,1c008d58 <pos_libc_prf+0x862>
1c008c1c:	4832                	lw	a6,12(sp)
1c008c1e:	004c0913          	addi	s2,s8,4
1c008c22:	000c2583          	lw	a1,0(s8)
1c008c26:	86d6                	mv	a3,s5
1c008c28:	4641                	li	a2,16
1c008c2a:	18080d63          	beqz	a6,1c008dc4 <pos_libc_prf+0x8ce>
1c008c2e:	7761                	lui	a4,0xffff8
1c008c30:	83074713          	xori	a4,a4,-2000
1c008c34:	02610513          	addi	a0,sp,38
1c008c38:	02e11223          	sh	a4,36(sp)
1c008c3c:	3899                	jal	1c008492 <pos_libc_to_x>
1c008c3e:	05800713          	li	a4,88
1c008c42:	89aa                	mv	s3,a0
1c008c44:	4aeb0463          	beq	s6,a4,1c0090ec <pos_libc_prf+0xbf6>
1c008c48:	4709                	li	a4,2
1c008c4a:	0989                	addi	s3,s3,2
1c008c4c:	c63a                	sw	a4,12(sp)
1c008c4e:	0c800793          	li	a5,200
1c008c52:	1bfaac63          	p.beqimm	s5,-1,1c008e0a <pos_libc_prf+0x914>
1c008c56:	a537c9e3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008c5a:	02000713          	li	a4,32
1c008c5e:	8c4a                	mv	s8,s2
1c008c60:	c83a                	sw	a4,16(sp)
1c008c62:	b705                	j	1c008b82 <pos_libc_prf+0x68c>
1c008c64:	c602                	sw	zero,12(sp)
1c008c66:	4872                	lw	a6,28(sp)
1c008c68:	013d0733          	add	a4,s10,s3
1c008c6c:	014d07b3          	add	a5,s10,s4
1c008c70:	02000693          	li	a3,32
1c008c74:	8f99                	sub	a5,a5,a4
1c008c76:	00080a63          	beqz	a6,1c008c8a <pos_libc_prf+0x794>
1c008c7a:	0047c0fb          	lp.setup	x1,a5,1c008c82 <pos_libc_prf+0x78c>
1c008c7e:	00d700ab          	p.sb	a3,1(a4!) # ffff8001 <pulp__FC+0xffff8002>
1c008c82:	0001                	nop
1c008c84:	a00a13e3          	bnez	s4,1c00868a <pos_libc_prf+0x194>
1c008c88:	b855                	j	1c00853c <pos_libc_prf+0x46>
1c008c8a:	413a0b33          	sub	s6,s4,s3
1c008c8e:	00198613          	addi	a2,s3,1
1c008c92:	85ea                	mv	a1,s10
1c008c94:	016d0533          	add	a0,s10,s6
1c008c98:	f24ff0ef          	jal	ra,1c0083bc <memmove>
1c008c9c:	4742                	lw	a4,16(sp)
1c008c9e:	02000793          	li	a5,32
1c008ca2:	36f70863          	beq	a4,a5,1c009012 <pos_libc_prf+0xb1c>
1c008ca6:	47b2                	lw	a5,12(sp)
1c008ca8:	9b3e                	add	s6,s6,a5
1c008caa:	ed67dfe3          	ble	s6,a5,1c008b88 <pos_libc_prf+0x692>
1c008cae:	4832                	lw	a6,12(sp)
1c008cb0:	4742                	lw	a4,16(sp)
1c008cb2:	010d07b3          	add	a5,s10,a6
1c008cb6:	410b0b33          	sub	s6,s6,a6
1c008cba:	004b40fb          	lp.setup	x1,s6,1c008cc2 <pos_libc_prf+0x7cc>
1c008cbe:	00e780ab          	p.sb	a4,1(a5!)
1c008cc2:	0001                	nop
1c008cc4:	9c0a13e3          	bnez	s4,1c00868a <pos_libc_prf+0x194>
1c008cc8:	b895                	j	1c00853c <pos_libc_prf+0x46>
1c008cca:	06900713          	li	a4,105
1c008cce:	08eb1563          	bne	s6,a4,1c008d58 <pos_libc_prf+0x862>
1c008cd2:	000c2583          	lw	a1,0(s8)
1c008cd6:	0c11                	addi	s8,s8,4
1c008cd8:	1e05c963          	bltz	a1,1c008eca <pos_libc_prf+0x9d4>
1c008cdc:	47d2                	lw	a5,20(sp)
1c008cde:	18079663          	bnez	a5,1c008e6a <pos_libc_prf+0x974>
1c008ce2:	4862                	lw	a6,24(sp)
1c008ce4:	32080963          	beqz	a6,1c009016 <pos_libc_prf+0xb20>
1c008ce8:	02000793          	li	a5,32
1c008cec:	02f10223          	sb	a5,36(sp)
1c008cf0:	4629                	li	a2,10
1c008cf2:	86d6                	mv	a3,s5
1c008cf4:	02510513          	addi	a0,sp,37
1c008cf8:	f9aff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008cfc:	02510613          	addi	a2,sp,37
1c008d00:	9532                	add	a0,a0,a2
1c008d02:	4705                	li	a4,1
1c008d04:	41a509b3          	sub	s3,a0,s10
1c008d08:	c63a                	sw	a4,12(sp)
1c008d0a:	e7faa8e3          	p.beqimm	s5,-1,1c008b7a <pos_libc_prf+0x684>
1c008d0e:	0c800793          	li	a5,200
1c008d12:	9937cbe3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008d16:	02000813          	li	a6,32
1c008d1a:	c842                	sw	a6,16(sp)
1c008d1c:	b59d                	j	1c008b82 <pos_libc_prf+0x68c>
1c008d1e:	000c2783          	lw	a5,0(s8)
1c008d22:	020102a3          	sb	zero,37(sp)
1c008d26:	0c11                	addi	s8,s8,4
1c008d28:	02f10223          	sb	a5,36(sp)
1c008d2c:	4985                	li	s3,1
1c008d2e:	ba99                	j	1c008684 <pos_libc_prf+0x18e>
1c008d30:	000c2583          	lw	a1,0(s8)
1c008d34:	86d6                	mv	a3,s5
1c008d36:	4629                	li	a2,10
1c008d38:	856a                	mv	a0,s10
1c008d3a:	f58ff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008d3e:	89aa                	mv	s3,a0
1c008d40:	0c11                	addi	s8,s8,4
1c008d42:	0c800793          	li	a5,200
1c008d46:	07faa463          	p.beqimm	s5,-1,1c008dae <pos_libc_prf+0x8b8>
1c008d4a:	94a7cfe3          	blt	a5,a0,1c0086a8 <pos_libc_prf+0x1b2>
1c008d4e:	02000793          	li	a5,32
1c008d52:	c602                	sw	zero,12(sp)
1c008d54:	c83e                	sw	a5,16(sp)
1c008d56:	b535                	j	1c008b82 <pos_libc_prf+0x68c>
1c008d58:	0c800713          	li	a4,200
1c008d5c:	ff675063          	ble	s6,a4,1c00853c <pos_libc_prf+0x46>
1c008d60:	547d                	li	s0,-1
1c008d62:	ffcff06f          	j	1c00855e <pos_libc_prf+0x68>
1c008d66:	000c2583          	lw	a1,0(s8)
1c008d6a:	77e1                	lui	a5,0xffff8
1c008d6c:	8307c793          	xori	a5,a5,-2000
1c008d70:	46a1                	li	a3,8
1c008d72:	4641                	li	a2,16
1c008d74:	02610513          	addi	a0,sp,38
1c008d78:	02f11223          	sh	a5,36(sp)
1c008d7c:	f16ff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008d80:	0c11                	addi	s8,s8,4
1c008d82:	00250993          	addi	s3,a0,2 # 10000002 <__l1_heap_size+0xfff000a>
1c008d86:	0c800793          	li	a5,200
1c008d8a:	03faa263          	p.beqimm	s5,-1,1c008dae <pos_libc_prf+0x8b8>
1c008d8e:	9137cde3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008d92:	02000813          	li	a6,32
1c008d96:	c602                	sw	zero,12(sp)
1c008d98:	c842                	sw	a6,16(sp)
1c008d9a:	b3e5                	j	1c008b82 <pos_libc_prf+0x68c>
1c008d9c:	000c2783          	lw	a5,0(s8)
1c008da0:	0c11                	addi	s8,s8,4
1c008da2:	c380                	sw	s0,0(a5)
1c008da4:	f98ff06f          	j	1c00853c <pos_libc_prf+0x46>
1c008da8:	8c0ad5e3          	bgez	s5,1c008672 <pos_libc_prf+0x17c>
1c008dac:	b0e9                	j	1c008676 <pos_libc_prf+0x180>
1c008dae:	8f37cde3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008db2:	c602                	sw	zero,12(sp)
1c008db4:	b3f9                	j	1c008b82 <pos_libc_prf+0x68c>
1c008db6:	0c800793          	li	a5,200
1c008dba:	8f37c7e3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008dbe:	4785                	li	a5,1
1c008dc0:	c63e                	sw	a5,12(sp)
1c008dc2:	b3c1                	j	1c008b82 <pos_libc_prf+0x68c>
1c008dc4:	856a                	mv	a0,s10
1c008dc6:	eccff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008dca:	05800713          	li	a4,88
1c008dce:	89aa                	mv	s3,a0
1c008dd0:	e6eb1fe3          	bne	s6,a4,1c008c4e <pos_libc_prf+0x758>
1c008dd4:	02414783          	lbu	a5,36(sp)
1c008dd8:	4601                	li	a2,0
1c008dda:	e6078ae3          	beqz	a5,1c008c4e <pos_libc_prf+0x758>
1c008dde:	876a                	mv	a4,s10
1c008de0:	45e5                	li	a1,25
1c008de2:	f9f78693          	addi	a3,a5,-97 # ffff7f9f <pulp__FC+0xffff7fa0>
1c008de6:	0ff6f693          	andi	a3,a3,255
1c008dea:	1781                	addi	a5,a5,-32
1c008dec:	00d5e463          	bltu	a1,a3,1c008df4 <pos_libc_prf+0x8fe>
1c008df0:	00f70023          	sb	a5,0(a4)
1c008df4:	0705                	addi	a4,a4,1
1c008df6:	00074783          	lbu	a5,0(a4)
1c008dfa:	f7e5                	bnez	a5,1c008de2 <pos_libc_prf+0x8ec>
1c008dfc:	47b2                	lw	a5,12(sp)
1c008dfe:	99b2                	add	s3,s3,a2
1c008e00:	e40787e3          	beqz	a5,1c008c4e <pos_libc_prf+0x758>
1c008e04:	4809                	li	a6,2
1c008e06:	c642                	sw	a6,12(sp)
1c008e08:	b599                	j	1c008c4e <pos_libc_prf+0x758>
1c008e0a:	8937cfe3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008e0e:	8c4a                	mv	s8,s2
1c008e10:	bb8d                	j	1c008b82 <pos_libc_prf+0x68c>
1c008e12:	47b2                	lw	a5,12(sp)
1c008e14:	4281                	li	t0,0
1c008e16:	e399                	bnez	a5,1c008e1c <pos_libc_prf+0x926>
1c008e18:	015032b3          	snez	t0,s5
1c008e1c:	5675                	li	a2,-3
1c008e1e:	001a8693          	addi	a3,s5,1
1c008e22:	00c34463          	blt	t1,a2,1c008e2a <pos_libc_prf+0x934>
1c008e26:	1a66d763          	ble	t1,a3,1c008fd4 <pos_libc_prf+0xade>
1c008e2a:	4841                	li	a6,16
1c008e2c:	0506ceb3          	p.min	t4,a3,a6
1c008e30:	06700693          	li	a3,103
1c008e34:	1efd                	addi	t4,t4,-1
1c008e36:	22db0f63          	beq	s6,a3,1c009074 <pos_libc_prf+0xb7e>
1c008e3a:	04500b13          	li	s6,69
1c008e3e:	b6b1                	j	1c00898a <pos_libc_prf+0x494>
1c008e40:	02510513          	addi	a0,sp,37
1c008e44:	86d6                	mv	a3,s5
1c008e46:	4621                	li	a2,8
1c008e48:	e4aff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008e4c:	4732                	lw	a4,12(sp)
1c008e4e:	0c800793          	li	a5,200
1c008e52:	00e509b3          	add	s3,a0,a4
1c008e56:	0dfaa163          	p.beqimm	s5,-1,1c008f18 <pos_libc_prf+0xa22>
1c008e5a:	8537c7e3          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008e5e:	02000713          	li	a4,32
1c008e62:	8c4a                	mv	s8,s2
1c008e64:	c602                	sw	zero,12(sp)
1c008e66:	c83a                	sw	a4,16(sp)
1c008e68:	bb29                	j	1c008b82 <pos_libc_prf+0x68c>
1c008e6a:	02b00793          	li	a5,43
1c008e6e:	02f10223          	sb	a5,36(sp)
1c008e72:	bdbd                	j	1c008cf0 <pos_libc_prf+0x7fa>
1c008e74:	856a                	mv	a0,s10
1c008e76:	b7f9                	j	1c008e44 <pos_libc_prf+0x94e>
1c008e78:	876a                	mv	a4,s10
1c008e7a:	24054863          	bltz	a0,1c0090ca <pos_libc_prf+0xbd4>
1c008e7e:	8ed1                	or	a3,a3,a2
1c008e80:	fbfb0793          	addi	a5,s6,-65
1c008e84:	00370893          	addi	a7,a4,3
1c008e88:	16069863          	bnez	a3,1c008ff8 <pos_libc_prf+0xb02>
1c008e8c:	46e5                	li	a3,25
1c008e8e:	22f6e463          	bltu	a3,a5,1c0090b6 <pos_libc_prf+0xbc0>
1c008e92:	6795                	lui	a5,0x5
1c008e94:	e4978793          	addi	a5,a5,-439 # 4e49 <__cluster_text_size+0x4e49>
1c008e98:	00f71023          	sh	a5,0(a4)
1c008e9c:	04600793          	li	a5,70
1c008ea0:	00f70123          	sb	a5,2(a4)
1c008ea4:	000701a3          	sb	zero,3(a4)
1c008ea8:	41a889b3          	sub	s3,a7,s10
1c008eac:	b95d                	j	1c008b62 <pos_libc_prf+0x66c>
1c008eae:	4652                	lw	a2,20(sp)
1c008eb0:	16060b63          	beqz	a2,1c009026 <pos_libc_prf+0xb30>
1c008eb4:	02b00713          	li	a4,43
1c008eb8:	02e10223          	sb	a4,36(sp)
1c008ebc:	02510f13          	addi	t5,sp,37
1c008ec0:	4301                	li	t1,0
1c008ec2:	4801                	li	a6,0
1c008ec4:	4681                	li	a3,0
1c008ec6:	4581                	li	a1,0
1c008ec8:	b4bd                	j	1c008936 <pos_libc_prf+0x440>
1c008eca:	02d00793          	li	a5,45
1c008ece:	02f10223          	sb	a5,36(sp)
1c008ed2:	800007b7          	lui	a5,0x80000
1c008ed6:	16f58b63          	beq	a1,a5,1c00904c <pos_libc_prf+0xb56>
1c008eda:	40b005b3          	neg	a1,a1
1c008ede:	86d6                	mv	a3,s5
1c008ee0:	4629                	li	a2,10
1c008ee2:	02510513          	addi	a0,sp,37
1c008ee6:	dacff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c008eea:	02510813          	addi	a6,sp,37
1c008eee:	9542                	add	a0,a0,a6
1c008ef0:	4705                	li	a4,1
1c008ef2:	41a509b3          	sub	s3,a0,s10
1c008ef6:	c63a                	sw	a4,12(sp)
1c008ef8:	bd09                	j	1c008d0a <pos_libc_prf+0x814>
1c008efa:	4a99                	li	s5,6
1c008efc:	a6db18e3          	bne	s6,a3,1c00896c <pos_libc_prf+0x476>
1c008f00:	4832                	lw	a6,12(sp)
1c008f02:	57f5                	li	a5,-3
1c008f04:	00184293          	xori	t0,a6,1
1c008f08:	16f35263          	ble	a5,t1,1c00906c <pos_libc_prf+0xb76>
1c008f0c:	001f0893          	addi	a7,t5,1
1c008f10:	06500b13          	li	s6,101
1c008f14:	4e99                	li	t4,6
1c008f16:	bca5                	j	1c00898e <pos_libc_prf+0x498>
1c008f18:	f937c863          	blt	a5,s3,1c0086a8 <pos_libc_prf+0x1b2>
1c008f1c:	8c4a                	mv	s8,s2
1c008f1e:	c602                	sw	zero,12(sp)
1c008f20:	b18d                	j	1c008b82 <pos_libc_prf+0x68c>
1c008f22:	be0a8de3          	beqz	s5,1c008b1c <pos_libc_prf+0x626>
1c008f26:	02e00693          	li	a3,46
1c008f2a:	002f0893          	addi	a7,t5,2
1c008f2e:	00df00a3          	sb	a3,1(t5)
1c008f32:	be51                	j	1c008ac6 <pos_libc_prf+0x5d0>
1c008f34:	10605663          	blez	t1,1c009040 <pos_libc_prf+0xb4a>
1c008f38:	006f08b3          	add	a7,t5,t1
1c008f3c:	45c1                	li	a1,16
1c008f3e:	41e88633          	sub	a2,a7,t5
1c008f42:	026640fb          	lp.setup	x1,a2,1c008f8e <pos_libc_prf+0xa98>
1c008f46:	002e1793          	slli	a5,t3,0x2
1c008f4a:	01ee5813          	srli	a6,t3,0x1e
1c008f4e:	00271693          	slli	a3,a4,0x2
1c008f52:	01c78533          	add	a0,a5,t3
1c008f56:	00d866b3          	or	a3,a6,a3
1c008f5a:	96ba                	add	a3,a3,a4
1c008f5c:	00f537b3          	sltu	a5,a0,a5
1c008f60:	97b6                	add	a5,a5,a3
1c008f62:	0786                	slli	a5,a5,0x1
1c008f64:	01f55693          	srli	a3,a0,0x1f
1c008f68:	8fd5                	or	a5,a5,a3
1c008f6a:	01c7d813          	srli	a6,a5,0x1c
1c008f6e:	03000693          	li	a3,48
1c008f72:	00b05c63          	blez	a1,1c008f8a <pos_libc_prf+0xa94>
1c008f76:	03080693          	addi	a3,a6,48 # 10000030 <__l2_shared_end+0x28>
1c008f7a:	10000837          	lui	a6,0x10000
1c008f7e:	187d                	addi	a6,a6,-1
1c008f80:	15fd                	addi	a1,a1,-1
1c008f82:	00151e13          	slli	t3,a0,0x1
1c008f86:	0107f733          	and	a4,a5,a6
1c008f8a:	00df00ab          	p.sb	a3,1(t5!)
1c008f8e:	0001                	nop
1c008f90:	4301                	li	t1,0
1c008f92:	47b2                	lw	a5,12(sp)
1c008f94:	e399                	bnez	a5,1c008f9a <pos_libc_prf+0xaa4>
1c008f96:	c40a85e3          	beqz	s5,1c008be0 <pos_libc_prf+0x6ea>
1c008f9a:	00188513          	addi	a0,a7,1
1c008f9e:	001a8793          	addi	a5,s5,1
1c008fa2:	02e00693          	li	a3,46
1c008fa6:	00d88023          	sb	a3,0(a7)
1c008faa:	862a                	mv	a2,a0
1c008fac:	98be                	add	a7,a7,a5
1c008fae:	03000793          	li	a5,48
1c008fb2:	c31605e3          	beq	a2,a7,1c008bdc <pos_libc_prf+0x6e6>
1c008fb6:	0605                	addi	a2,a2,1
1c008fb8:	bc030ce3          	beqz	t1,1c008b90 <pos_libc_prf+0x69a>
1c008fbc:	fef60fa3          	sb	a5,-1(a2)
1c008fc0:	0305                	addi	t1,t1,1
1c008fc2:	bfc5                	j	1c008fb2 <pos_libc_prf+0xabc>
1c008fc4:	02d00793          	li	a5,45
1c008fc8:	40600333          	neg	t1,t1
1c008fcc:	00f880a3          	sb	a5,1(a7)
1c008fd0:	b6bd                	j	1c008b3e <pos_libc_prf+0x648>
1c008fd2:	4281                	li	t0,0
1c008fd4:	015307b3          	add	a5,t1,s5
1c008fd8:	001f0893          	addi	a7,t5,1
1c008fdc:	0e07ce63          	bltz	a5,1c0090d8 <pos_libc_prf+0xbe2>
1c008fe0:	4641                	li	a2,16
1c008fe2:	04c7ceb3          	p.min	t4,a5,a2
1c008fe6:	1efd                	addi	t4,t4,-1
1c008fe8:	06600b13          	li	s6,102
1c008fec:	9a0791e3          	bnez	a5,1c00898e <pos_libc_prf+0x498>
1c008ff0:	4601                	li	a2,0
1c008ff2:	080006b7          	lui	a3,0x8000
1c008ff6:	b401                	j	1c0089f6 <pos_libc_prf+0x500>
1c008ff8:	46e5                	li	a3,25
1c008ffa:	08f6e063          	bltu	a3,a5,1c00907a <pos_libc_prf+0xb84>
1c008ffe:	6791                	lui	a5,0x4
1c009000:	14e78793          	addi	a5,a5,334 # 414e <__cluster_text_size+0x414e>
1c009004:	00f71023          	sh	a5,0(a4)
1c009008:	04e00793          	li	a5,78
1c00900c:	00f70123          	sb	a5,2(a4)
1c009010:	bd51                	j	1c008ea4 <pos_libc_prf+0x9ae>
1c009012:	c602                	sw	zero,12(sp)
1c009014:	b969                	j	1c008cae <pos_libc_prf+0x7b8>
1c009016:	86d6                	mv	a3,s5
1c009018:	4629                	li	a2,10
1c00901a:	856a                	mv	a0,s10
1c00901c:	c76ff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c009020:	89aa                	mv	s3,a0
1c009022:	c602                	sw	zero,12(sp)
1c009024:	b1dd                	j	1c008d0a <pos_libc_prf+0x814>
1c009026:	47e2                	lw	a5,24(sp)
1c009028:	cbe1                	beqz	a5,1c0090f8 <pos_libc_prf+0xc02>
1c00902a:	02000713          	li	a4,32
1c00902e:	02e10223          	sb	a4,36(sp)
1c009032:	02510f13          	addi	t5,sp,37
1c009036:	4301                	li	t1,0
1c009038:	4801                	li	a6,0
1c00903a:	4681                	li	a3,0
1c00903c:	4581                	li	a1,0
1c00903e:	b8e5                	j	1c008936 <pos_libc_prf+0x440>
1c009040:	03000793          	li	a5,48
1c009044:	00ff0023          	sb	a5,0(t5)
1c009048:	45c1                	li	a1,16
1c00904a:	b7a1                	j	1c008f92 <pos_libc_prf+0xa9c>
1c00904c:	86d6                	mv	a3,s5
1c00904e:	4629                	li	a2,10
1c009050:	800005b7          	lui	a1,0x80000
1c009054:	02510513          	addi	a0,sp,37
1c009058:	c3aff0ef          	jal	ra,1c008492 <pos_libc_to_x>
1c00905c:	02510793          	addi	a5,sp,37
1c009060:	953e                	add	a0,a0,a5
1c009062:	4805                	li	a6,1
1c009064:	41a509b3          	sub	s3,a0,s10
1c009068:	c642                	sw	a6,12(sp)
1c00906a:	b145                	j	1c008d0a <pos_libc_prf+0x814>
1c00906c:	479d                	li	a5,7
1c00906e:	f667d3e3          	ble	t1,a5,1c008fd4 <pos_libc_prf+0xade>
1c009072:	4e99                	li	t4,6
1c009074:	06500b13          	li	s6,101
1c009078:	ba09                	j	1c00898a <pos_libc_prf+0x494>
1c00907a:	6799                	lui	a5,0x6
1c00907c:	16e78793          	addi	a5,a5,366 # 616e <__cluster_text_size+0x616e>
1c009080:	00f71023          	sh	a5,0(a4)
1c009084:	06e00793          	li	a5,110
1c009088:	00f70123          	sb	a5,2(a4)
1c00908c:	bd21                	j	1c008ea4 <pos_libc_prf+0x9ae>
1c00908e:	47e2                	lw	a5,24(sp)
1c009090:	8f6a                	mv	t5,s10
1c009092:	fc078463          	beqz	a5,1c00885a <pos_libc_prf+0x364>
1c009096:	02000713          	li	a4,32
1c00909a:	02e10223          	sb	a4,36(sp)
1c00909e:	02510f13          	addi	t5,sp,37
1c0090a2:	fb8ff06f          	j	1c00885a <pos_libc_prf+0x364>
1c0090a6:	02d00713          	li	a4,45
1c0090aa:	02e10223          	sb	a4,36(sp)
1c0090ae:	02510f13          	addi	t5,sp,37
1c0090b2:	fa8ff06f          	j	1c00885a <pos_libc_prf+0x364>
1c0090b6:	679d                	lui	a5,0x7
1c0090b8:	e6978793          	addi	a5,a5,-407 # 6e69 <__cluster_text_size+0x6e69>
1c0090bc:	00f71023          	sh	a5,0(a4)
1c0090c0:	06600793          	li	a5,102
1c0090c4:	00f70123          	sb	a5,2(a4)
1c0090c8:	bbf1                	j	1c008ea4 <pos_libc_prf+0x9ae>
1c0090ca:	02d00713          	li	a4,45
1c0090ce:	02e10223          	sb	a4,36(sp)
1c0090d2:	02510713          	addi	a4,sp,37
1c0090d6:	b365                	j	1c008e7e <pos_libc_prf+0x988>
1c0090d8:	080007b7          	lui	a5,0x8000
1c0090dc:	973e                	add	a4,a4,a5
1c0090de:	f60737b3          	p.bclr	a5,a4,27,0
1c0090e2:	e40789e3          	beqz	a5,1c008f34 <pos_libc_prf+0xa3e>
1c0090e6:	06600b13          	li	s6,102
1c0090ea:	ba39                	j	1c008a08 <pos_libc_prf+0x512>
1c0090ec:	02414783          	lbu	a5,36(sp)
1c0090f0:	4609                	li	a2,2
1c0090f2:	ce0796e3          	bnez	a5,1c008dde <pos_libc_prf+0x8e8>
1c0090f6:	be89                	j	1c008c48 <pos_libc_prf+0x752>
1c0090f8:	8f6a                	mv	t5,s10
1c0090fa:	bf35                	j	1c009036 <pos_libc_prf+0xb40>

1c0090fc <pos_init_start>:
1c0090fc:	1141                	addi	sp,sp,-16
1c0090fe:	c422                	sw	s0,8(sp)
1c009100:	1c000437          	lui	s0,0x1c000
1c009104:	c606                	sw	ra,12(sp)
1c009106:	00840413          	addi	s0,s0,8 # 1c000008 <ctor_list>
1c00910a:	a1aff0ef          	jal	ra,1c008324 <pos_soc_init>
1c00910e:	2279                	jal	1c00929c <pos_irq_init>
1c009110:	2ac1                	jal	1c0092e0 <pos_soc_event_init>
1c009112:	20e5                	jal	1c0091fa <pos_allocs_init>
1c009114:	405c                	lw	a5,4(s0)
1c009116:	c791                	beqz	a5,1c009122 <pos_init_start+0x26>
1c009118:	0421                	addi	s0,s0,8
1c00911a:	9782                	jalr	a5
1c00911c:	0044278b          	p.lw	a5,4(s0!)
1c009120:	ffed                	bnez	a5,1c00911a <pos_init_start+0x1e>
1c009122:	b3aff0ef          	jal	ra,1c00845c <pos_io_start>
1c009126:	300467f3          	csrrsi	a5,mstatus,8
1c00912a:	f1402573          	csrr	a0,mhartid
1c00912e:	8515                	srai	a0,a0,0x5
1c009130:	f2653533          	p.bclr	a0,a0,25,6
1c009134:	47fd                	li	a5,31
1c009136:	00f50a63          	beq	a0,a5,1c00914a <pos_init_start+0x4e>
1c00913a:	4422                	lw	s0,8(sp)
1c00913c:	40b2                	lw	ra,12(sp)
1c00913e:	1c0085b7          	lui	a1,0x1c008
1c009142:	17a58593          	addi	a1,a1,378 # 1c00817a <main>
1c009146:	0141                	addi	sp,sp,16
1c009148:	a405                	j	1c009368 <cluster_start>
1c00914a:	40b2                	lw	ra,12(sp)
1c00914c:	4422                	lw	s0,8(sp)
1c00914e:	0141                	addi	sp,sp,16
1c009150:	8082                	ret

1c009152 <pos_init_stop>:
1c009152:	1141                	addi	sp,sp,-16
1c009154:	c422                	sw	s0,8(sp)
1c009156:	1c000437          	lui	s0,0x1c000
1c00915a:	c606                	sw	ra,12(sp)
1c00915c:	01440413          	addi	s0,s0,20 # 1c000014 <dtor_list>
1c009160:	b00ff0ef          	jal	ra,1c008460 <pos_io_stop>
1c009164:	405c                	lw	a5,4(s0)
1c009166:	c791                	beqz	a5,1c009172 <pos_init_stop+0x20>
1c009168:	0421                	addi	s0,s0,8
1c00916a:	9782                	jalr	a5
1c00916c:	0044278b          	p.lw	a5,4(s0!)
1c009170:	ffed                	bnez	a5,1c00916a <pos_init_stop+0x18>
1c009172:	40b2                	lw	ra,12(sp)
1c009174:	4422                	lw	s0,8(sp)
1c009176:	0141                	addi	sp,sp,16
1c009178:	8082                	ret

1c00917a <pos_alloc_init>:
1c00917a:	00758793          	addi	a5,a1,7
1c00917e:	c407b7b3          	p.bclr	a5,a5,2,0
1c009182:	40b785b3          	sub	a1,a5,a1
1c009186:	c11c                	sw	a5,0(a0)
1c009188:	8e0d                	sub	a2,a2,a1
1c00918a:	00c05763          	blez	a2,1c009198 <pos_alloc_init+0x1e>
1c00918e:	c4063633          	p.bclr	a2,a2,2,0
1c009192:	c390                	sw	a2,0(a5)
1c009194:	0007a223          	sw	zero,4(a5) # 8000004 <__l1_heap_size+0x7ff000c>
1c009198:	8082                	ret

1c00919a <pos_alloc>:
1c00919a:	4110                	lw	a2,0(a0)
1c00919c:	059d                	addi	a1,a1,7
1c00919e:	c405b5b3          	p.bclr	a1,a1,2,0
1c0091a2:	ca31                	beqz	a2,1c0091f6 <pos_alloc+0x5c>
1c0091a4:	4218                	lw	a4,0(a2)
1c0091a6:	425c                	lw	a5,4(a2)
1c0091a8:	02b75963          	ble	a1,a4,1c0091da <pos_alloc+0x40>
1c0091ac:	cb81                	beqz	a5,1c0091bc <pos_alloc+0x22>
1c0091ae:	4398                	lw	a4,0(a5)
1c0091b0:	43d4                	lw	a3,4(a5)
1c0091b2:	00b75763          	ble	a1,a4,1c0091c0 <pos_alloc+0x26>
1c0091b6:	863e                	mv	a2,a5
1c0091b8:	87b6                	mv	a5,a3
1c0091ba:	fbf5                	bnez	a5,1c0091ae <pos_alloc+0x14>
1c0091bc:	853e                	mv	a0,a5
1c0091be:	8082                	ret
1c0091c0:	00b70a63          	beq	a4,a1,1c0091d4 <pos_alloc+0x3a>
1c0091c4:	00b78533          	add	a0,a5,a1
1c0091c8:	8f0d                	sub	a4,a4,a1
1c0091ca:	c118                	sw	a4,0(a0)
1c0091cc:	c154                	sw	a3,4(a0)
1c0091ce:	c248                	sw	a0,4(a2)
1c0091d0:	853e                	mv	a0,a5
1c0091d2:	8082                	ret
1c0091d4:	c254                	sw	a3,4(a2)
1c0091d6:	853e                	mv	a0,a5
1c0091d8:	8082                	ret
1c0091da:	00e58b63          	beq	a1,a4,1c0091f0 <pos_alloc+0x56>
1c0091de:	00b606b3          	add	a3,a2,a1
1c0091e2:	8f0d                	sub	a4,a4,a1
1c0091e4:	c2dc                	sw	a5,4(a3)
1c0091e6:	c298                	sw	a4,0(a3)
1c0091e8:	87b2                	mv	a5,a2
1c0091ea:	c114                	sw	a3,0(a0)
1c0091ec:	853e                	mv	a0,a5
1c0091ee:	8082                	ret
1c0091f0:	c11c                	sw	a5,0(a0)
1c0091f2:	87b2                	mv	a5,a2
1c0091f4:	b7e1                	j	1c0091bc <pos_alloc+0x22>
1c0091f6:	4781                	li	a5,0
1c0091f8:	b7d1                	j	1c0091bc <pos_alloc+0x22>

1c0091fa <pos_allocs_init>:
1c0091fa:	1141                	addi	sp,sp,-16
1c0091fc:	1c0015b7          	lui	a1,0x1c001
1c009200:	c606                	sw	ra,12(sp)
1c009202:	c8858793          	addi	a5,a1,-888 # 1c000c88 <__l2_priv0_end>
1c009206:	1c008637          	lui	a2,0x1c008
1c00920a:	04c7cc63          	blt	a5,a2,1c009262 <pos_allocs_init+0x68>
1c00920e:	4581                	li	a1,0
1c009210:	4601                	li	a2,0
1c009212:	1c001537          	lui	a0,0x1c001
1c009216:	c7850513          	addi	a0,a0,-904 # 1c000c78 <pos_alloc_l2>
1c00921a:	3785                	jal	1c00917a <pos_alloc_init>
1c00921c:	1c0095b7          	lui	a1,0x1c009
1c009220:	41458793          	addi	a5,a1,1044 # 1c009414 <__l2_priv1_end>
1c009224:	1c010637          	lui	a2,0x1c010
1c009228:	02c7c963          	blt	a5,a2,1c00925a <pos_allocs_init+0x60>
1c00922c:	4581                	li	a1,0
1c00922e:	4601                	li	a2,0
1c009230:	1c001537          	lui	a0,0x1c001
1c009234:	c7c50513          	addi	a0,a0,-900 # 1c000c7c <pos_alloc_l2+0x4>
1c009238:	3789                	jal	1c00917a <pos_alloc_init>
1c00923a:	100005b7          	lui	a1,0x10000
1c00923e:	40b2                	lw	ra,12(sp)
1c009240:	00858793          	addi	a5,a1,8 # 10000008 <__l2_shared_end>
1c009244:	1c080637          	lui	a2,0x1c080
1c009248:	1c001537          	lui	a0,0x1c001
1c00924c:	8e1d                	sub	a2,a2,a5
1c00924e:	00858593          	addi	a1,a1,8
1c009252:	c8050513          	addi	a0,a0,-896 # 1c000c80 <pos_alloc_l2+0x8>
1c009256:	0141                	addi	sp,sp,16
1c009258:	b70d                	j	1c00917a <pos_alloc_init>
1c00925a:	8e1d                	sub	a2,a2,a5
1c00925c:	41458593          	addi	a1,a1,1044
1c009260:	bfc1                	j	1c009230 <pos_allocs_init+0x36>
1c009262:	8e1d                	sub	a2,a2,a5
1c009264:	c8858593          	addi	a1,a1,-888
1c009268:	b76d                	j	1c009212 <pos_allocs_init+0x18>

1c00926a <alloc_init_l1>:
1c00926a:	100007b7          	lui	a5,0x10000
1c00926e:	01651593          	slli	a1,a0,0x16
1c009272:	00878793          	addi	a5,a5,8 # 10000008 <__l2_shared_end>
1c009276:	95be                	add	a1,a1,a5
1c009278:	1c0017b7          	lui	a5,0x1c001
1c00927c:	050a                	slli	a0,a0,0x2
1c00927e:	6641                	lui	a2,0x10
1c009280:	c7478793          	addi	a5,a5,-908 # 1c000c74 <pos_alloc_l1>
1c009284:	ff860613          	addi	a2,a2,-8 # fff8 <__l1_heap_size>
1c009288:	953e                	add	a0,a0,a5
1c00928a:	bdc5                	j	1c00917a <pos_alloc_init>

1c00928c <pi_l1_malloc>:
1c00928c:	1c0017b7          	lui	a5,0x1c001
1c009290:	050a                	slli	a0,a0,0x2
1c009292:	c7478793          	addi	a5,a5,-908 # 1c000c74 <pos_alloc_l1>
1c009296:	953e                	add	a0,a0,a5
1c009298:	b709                	j	1c00919a <pos_alloc>

1c00929a <__rt_handle_illegal_instr>:
1c00929a:	8082                	ret

1c00929c <pos_irq_init>:
1c00929c:	f14027f3          	csrr	a5,mhartid
1c0092a0:	477d                	li	a4,31
1c0092a2:	ca5797b3          	p.extractu	a5,a5,5,5
1c0092a6:	00e78f63          	beq	a5,a4,1c0092c4 <pos_irq_init+0x28>
1c0092aa:	002047b7          	lui	a5,0x204
1c0092ae:	577d                	li	a4,-1
1c0092b0:	cb98                	sw	a4,16(a5)
1c0092b2:	1c0087b7          	lui	a5,0x1c008
1c0092b6:	00078793          	mv	a5,a5
1c0092ba:	c007c7b3          	p.bset	a5,a5,0,0
1c0092be:	30579073          	csrw	mtvec,a5
1c0092c2:	8082                	ret
1c0092c4:	1a10a7b7          	lui	a5,0x1a10a
1c0092c8:	577d                	li	a4,-1
1c0092ca:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c0092ce:	1c0087b7          	lui	a5,0x1c008
1c0092d2:	00078793          	mv	a5,a5
1c0092d6:	c007c7b3          	p.bset	a5,a5,0,0
1c0092da:	30579073          	csrw	mtvec,a5
1c0092de:	8082                	ret

1c0092e0 <pos_soc_event_init>:
1c0092e0:	1a1067b7          	lui	a5,0x1a106
1c0092e4:	577d                	li	a4,-1
1c0092e6:	00478693          	addi	a3,a5,4 # 1a106004 <__l2_shared_end+0xa105ffc>
1c0092ea:	c298                	sw	a4,0(a3)
1c0092ec:	00878693          	addi	a3,a5,8
1c0092f0:	c298                	sw	a4,0(a3)
1c0092f2:	00c78693          	addi	a3,a5,12
1c0092f6:	c298                	sw	a4,0(a3)
1c0092f8:	01078693          	addi	a3,a5,16
1c0092fc:	c298                	sw	a4,0(a3)
1c0092fe:	01478693          	addi	a3,a5,20
1c009302:	c298                	sw	a4,0(a3)
1c009304:	01878693          	addi	a3,a5,24
1c009308:	c298                	sw	a4,0(a3)
1c00930a:	01c78693          	addi	a3,a5,28
1c00930e:	c298                	sw	a4,0(a3)
1c009310:	02078793          	addi	a5,a5,32
1c009314:	c398                	sw	a4,0(a5)
1c009316:	8082                	ret

1c009318 <cluster_entry_stub>:
1c009318:	1141                	addi	sp,sp,-16
1c00931a:	c606                	sw	ra,12(sp)
1c00931c:	002047b7          	lui	a5,0x204
1c009320:	00070737          	lui	a4,0x70
1c009324:	c798                	sw	a4,8(a5)
1c009326:	0ff00713          	li	a4,255
1c00932a:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c00932e:	00e7a023          	sw	a4,0(a5)
1c009332:	00e7a623          	sw	a4,12(a5)
1c009336:	1c0017b7          	lui	a5,0x1c001
1c00933a:	c847a783          	lw	a5,-892(a5) # 1c000c84 <cluster_entry>
1c00933e:	9782                	jalr	a5
1c009340:	f14027f3          	csrr	a5,mhartid
1c009344:	f457b7b3          	p.bclr	a5,a5,26,5
1c009348:	eb89                	bnez	a5,1c00935a <cluster_entry_stub+0x42>
1c00934a:	1c001737          	lui	a4,0x1c001
1c00934e:	1c0017b7          	lui	a5,0x1c001
1c009352:	c4a72a23          	sw	a0,-940(a4) # 1c000c54 <cluster_retval>
1c009356:	c407ac23          	sw	zero,-936(a5) # 1c000c58 <cluster_running>
1c00935a:	002047b7          	lui	a5,0x204
1c00935e:	577d                	li	a4,-1
1c009360:	c3d8                	sw	a4,4(a5)
1c009362:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c009366:	a001                	j	1c009366 <cluster_entry_stub+0x4e>

1c009368 <cluster_start>:
1c009368:	1141                	addi	sp,sp,-16
1c00936a:	1c0017b7          	lui	a5,0x1c001
1c00936e:	c226                	sw	s1,4(sp)
1c009370:	84aa                	mv	s1,a0
1c009372:	4509                	li	a0,2
1c009374:	c8b7a223          	sw	a1,-892(a5) # 1c000c84 <cluster_entry>
1c009378:	c606                	sw	ra,12(sp)
1c00937a:	c422                	sw	s0,8(sp)
1c00937c:	edffe0ef          	jal	ra,1c00825a <pos_fll_init>
1c009380:	8526                	mv	a0,s1
1c009382:	35e5                	jal	1c00926a <alloc_init_l1>
1c009384:	04048413          	addi	s0,s1,64
1c009388:	00201737          	lui	a4,0x201
1c00938c:	40070713          	addi	a4,a4,1024 # 201400 <__l1_heap_size+0x1f1408>
1c009390:	045a                	slli	s0,s0,0x16
1c009392:	56fd                	li	a3,-1
1c009394:	f14027f3          	csrr	a5,mhartid
1c009398:	00d46723          	p.sw	a3,a4(s0)
1c00939c:	ca5797b3          	p.extractu	a5,a5,5,5
1c0093a0:	477d                	li	a4,31
1c0093a2:	00e78f63          	beq	a5,a4,1c0093c0 <cluster_start+0x58>
1c0093a6:	002047b7          	lui	a5,0x204
1c0093aa:	00070737          	lui	a4,0x70
1c0093ae:	c798                	sw	a4,8(a5)
1c0093b0:	0ff00713          	li	a4,255
1c0093b4:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c0093b8:	00e7a023          	sw	a4,0(a5)
1c0093bc:	00e7a623          	sw	a4,12(a5)
1c0093c0:	8526                	mv	a0,s1
1c0093c2:	3565                	jal	1c00926a <alloc_init_l1>
1c0093c4:	6591                	lui	a1,0x4
1c0093c6:	8526                	mv	a0,s1
1c0093c8:	35d1                	jal	1c00928c <pi_l1_malloc>
1c0093ca:	100007b7          	lui	a5,0x10000
1c0093ce:	00a7a223          	sw	a0,4(a5) # 10000004 <cluster_stacks>
1c0093d2:	c91d                	beqz	a0,1c009408 <cluster_start+0xa0>
1c0093d4:	1c0017b7          	lui	a5,0x1c001
1c0093d8:	4705                	li	a4,1
1c0093da:	c4e7ac23          	sw	a4,-936(a5) # 1c000c58 <cluster_running>
1c0093de:	00200737          	lui	a4,0x200
1c0093e2:	1c0086b7          	lui	a3,0x1c008
1c0093e6:	04070713          	addi	a4,a4,64 # 200040 <__l1_heap_size+0x1f0048>
1c0093ea:	08068693          	addi	a3,a3,128 # 1c008080 <_start>
1c0093ee:	9722                	add	a4,a4,s0
1c0093f0:	008250fb          	lp.setupi	x1,8,1c0093f8 <cluster_start+0x90>
1c0093f4:	00d7222b          	p.sw	a3,4(a4!)
1c0093f8:	0001                	nop
1c0093fa:	002007b7          	lui	a5,0x200
1c0093fe:	07a1                	addi	a5,a5,8
1c009400:	0ff00713          	li	a4,255
1c009404:	00e467a3          	p.sw	a4,a5(s0)
1c009408:	40b2                	lw	ra,12(sp)
1c00940a:	4422                	lw	s0,8(sp)
1c00940c:	4492                	lw	s1,4(sp)
1c00940e:	0141                	addi	sp,sp,16
1c009410:	8082                	ret

1c009412 <_endtext>:
	...

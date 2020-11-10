riscv32-unknown-elf-objdump -Mmarch=rv32imcxgap9 -d /scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/reg_access/all_reg_rw_spim/build/test/test

/scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/reg_access/all_reg_rw_spim/build/test/test:     file format elf32-littleriscv


Disassembly of section .vectors:

1c008000 <__irq_vector_base>:
1c008000:	0450106f          	j	1c009844 <__rt_handle_illegal_instr>
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
1c008084:	7c00106f          	j	1c009844 <__rt_handle_illegal_instr>

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
1c0080b4:	00f0106f          	j	1c0098c2 <cluster_entry_stub>

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
1c0080f8:	ffff8297          	auipc	t0,0xffff8
1c0080fc:	77828293          	addi	t0,t0,1912 # 1c000870 <stack>
1c008100:	ffff8317          	auipc	t1,0xffff8
1c008104:	7a830313          	addi	t1,t1,1960 # 1c0008a8 <__l2_priv0_end>
1c008108:	0002a023          	sw	zero,0(t0)
1c00810c:	0291                	addi	t0,t0,4
1c00810e:	fe62ede3          	bltu	t0,t1,1c008108 <_stext+0x24>
1c008112:	ffff8117          	auipc	sp,0xffff8
1c008116:	75e10113          	addi	sp,sp,1886 # 1c000870 <stack>
1c00811a:	58c010ef          	jal	ra,1c0096a6 <pos_init_start>
1c00811e:	00000513          	li	a0,0
1c008122:	00000593          	li	a1,0
1c008126:	00000397          	auipc	t2,0x0
1c00812a:	01838393          	addi	t2,t2,24 # 1c00813e <main>
1c00812e:	000380e7          	jalr	t2
1c008132:	842a                	mv	s0,a0
1c008134:	5c8010ef          	jal	ra,1c0096fc <pos_init_stop>
1c008138:	8522                	mv	a0,s0
1c00813a:	608000ef          	jal	ra,1c008742 <exit>

1c00813e <main>:
1c00813e:	1c0007b7          	lui	a5,0x1c000
1c008142:	01c7a783          	lw	a5,28(a5) # 1c00001c <__DTOR_END__>
1c008146:	7139                	addi	sp,sp,-64
1c008148:	c002                	sw	zero,0(sp)
1c00814a:	00f120a3          	sw	a5,1(sp)
1c00814e:	1c0007b7          	lui	a5,0x1c000
1c008152:	0207a783          	lw	a5,32(a5) # 1c000020 <__DTOR_END__+0x4>
1c008156:	ce5e                	sw	s7,28(sp)
1c008158:	00011623          	sh	zero,12(sp)
1c00815c:	00f122a3          	sw	a5,5(sp)
1c008160:	1c0007b7          	lui	a5,0x1c000
1c008164:	0247a783          	lw	a5,36(a5) # 1c000024 <__DTOR_END__+0x8>
1c008168:	1a102bb7          	lui	s7,0x1a102
1c00816c:	d84a                	sw	s2,48(sp)
1c00816e:	d64e                	sw	s3,44(sp)
1c008170:	d452                	sw	s4,40(sp)
1c008172:	d256                	sw	s5,36(sp)
1c008174:	d05a                	sw	s6,32(sp)
1c008176:	cc62                	sw	s8,24(sp)
1c008178:	ca66                	sw	s9,20(sp)
1c00817a:	de06                	sw	ra,60(sp)
1c00817c:	dc22                	sw	s0,56(sp)
1c00817e:	da26                	sw	s1,52(sp)
1c008180:	00f124a3          	sw	a5,9(sp)
1c008184:	4c01                	li	s8,0
1c008186:	1c000cb7          	lui	s9,0x1c000
1c00818a:	00a10b13          	addi	s6,sp,10
1c00818e:	1c000ab7          	lui	s5,0x1c000
1c008192:	1c000a37          	lui	s4,0x1c000
1c008196:	100b8993          	addi	s3,s7,256 # 1a102100 <__l2_shared_end+0xa1020f8>
1c00819a:	597d                	li	s2,-1
1c00819c:	000ba783          	lw	a5,0(s7)
1c0081a0:	85e2                	mv	a1,s8
1c0081a2:	028c8513          	addi	a0,s9,40 # 1c000028 <__DTOR_END__+0xc>
1c0081a6:	c017c7b3          	p.bset	a5,a5,0,1
1c0081aa:	00fba023          	sw	a5,0(s7)
1c0081ae:	237d                	jal	1c00875c <printf>
1c0081b0:	848a                	mv	s1,sp
1c0081b2:	0014c40b          	p.lbu	s0,1(s1!)
1c0081b6:	55fd                	li	a1,-1
1c0081b8:	034a8513          	addi	a0,s5,52 # 1c000034 <__DTOR_END__+0x18>
1c0081bc:	944e                	add	s0,s0,s3
1c0081be:	01242023          	sw	s2,0(s0)
1c0081c2:	8622                	mv	a2,s0
1c0081c4:	2b61                	jal	1c00875c <printf>
1c0081c6:	400c                	lw	a1,0(s0)
1c0081c8:	044a0513          	addi	a0,s4,68 # 1c000044 <__DTOR_END__+0x28>
1c0081cc:	2b41                	jal	1c00875c <printf>
1c0081ce:	fe9b12e3          	bne	s6,s1,1c0081b2 <main+0x74>
1c0081d2:	000ba783          	lw	a5,0(s7)
1c0081d6:	c017b7b3          	p.bclr	a5,a5,0,1
1c0081da:	00fba023          	sw	a5,0(s7)
1c0081de:	021c3063          	p.bneimm	s8,1,1c0081fe <main+0xc0>
1c0081e2:	50f2                	lw	ra,60(sp)
1c0081e4:	5462                	lw	s0,56(sp)
1c0081e6:	54d2                	lw	s1,52(sp)
1c0081e8:	5942                	lw	s2,48(sp)
1c0081ea:	59b2                	lw	s3,44(sp)
1c0081ec:	5a22                	lw	s4,40(sp)
1c0081ee:	5a92                	lw	s5,36(sp)
1c0081f0:	5b02                	lw	s6,32(sp)
1c0081f2:	4bf2                	lw	s7,28(sp)
1c0081f4:	4c62                	lw	s8,24(sp)
1c0081f6:	4cd2                	lw	s9,20(sp)
1c0081f8:	4501                	li	a0,0
1c0081fa:	6121                	addi	sp,sp,64
1c0081fc:	8082                	ret
1c0081fe:	4c05                	li	s8,1
1c008200:	bf71                	j	1c00819c <main+0x5e>

1c008202 <pos_fll_init>:
1c008202:	00451613          	slli	a2,a0,0x4
1c008206:	85aa                	mv	a1,a0
1c008208:	00460813          	addi	a6,a2,4
1c00820c:	1a1006b7          	lui	a3,0x1a100
1c008210:	2106f783          	p.lw	a5,a6(a3)
1c008214:	873e                	mv	a4,a5
1c008216:	0407c163          	bltz	a5,1c008258 <pos_fll_init+0x56>
1c00821a:	00860313          	addi	t1,a2,8
1c00821e:	2066f883          	p.lw	a7,t1(a3)
1c008222:	4519                	li	a0,6
1c008224:	caa528b3          	p.insert	a7,a0,5,10
1c008228:	05000513          	li	a0,80
1c00822c:	d70528b3          	p.insert	a7,a0,11,16
1c008230:	1a100537          	lui	a0,0x1a100
1c008234:	01156323          	p.sw	a7,t1(a0)
1c008238:	0631                	addi	a2,a2,12
1c00823a:	20c6f683          	p.lw	a3,a2(a3)
1c00823e:	14c00893          	li	a7,332
1c008242:	d308a6b3          	p.insert	a3,a7,9,16
1c008246:	00d56623          	p.sw	a3,a2(a0)
1c00824a:	4685                	li	a3,1
1c00824c:	c1e6a733          	p.insert	a4,a3,0,30
1c008250:	c1f6a733          	p.insert	a4,a3,0,31
1c008254:	00e56823          	p.sw	a4,a6(a0)
1c008258:	1c0016b7          	lui	a3,0x1c001
1c00825c:	00259893          	slli	a7,a1,0x2
1c008260:	87c68693          	addi	a3,a3,-1924 # 1c00087c <pos_fll_freq>
1c008264:	01168633          	add	a2,a3,a7
1c008268:	4208                	lw	a0,0(a2)
1c00826a:	e115                	bnez	a0,1c00828e <pos_fll_init+0x8c>
1c00826c:	1007d7b3          	p.exthz	a5,a5
1c008270:	c7a71733          	p.extractu	a4,a4,3,26
1c008274:	07be                	slli	a5,a5,0xf
1c008276:	177d                	addi	a4,a4,-1
1c008278:	00e7d533          	srl	a0,a5,a4
1c00827c:	1c0017b7          	lui	a5,0x1c001
1c008280:	c208                	sw	a0,0(a2)
1c008282:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c008286:	4705                	li	a4,1
1c008288:	00e7c5a3          	p.sb	a4,a1(a5)
1c00828c:	8082                	ret
1c00828e:	10051733          	p.fl1	a4,a0
1c008292:	47f5                	li	a5,29
1c008294:	82e7b75b          	p.subun	a4,a5,a4,1
1c008298:	e731                	bnez	a4,1c0082e4 <pos_fll_init+0xe2>
1c00829a:	4f09                	li	t5,2
1c00829c:	4e05                	li	t3,1
1c00829e:	4705                	li	a4,1
1c0082a0:	1c0017b7          	lui	a5,0x1c001
1c0082a4:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c0082a8:	00e51333          	sll	t1,a0,a4
1c0082ac:	00b78eb3          	add	t4,a5,a1
1c0082b0:	dc033633          	p.bclr	a2,t1,14,0
1c0082b4:	000ece83          	lbu	t4,0(t4)
1c0082b8:	c0ee265b          	p.addunr	a2,t3,a4
1c0082bc:	00c6e8a3          	p.sw	a2,a7(a3)
1c0082c0:	fc0e83e3          	beqz	t4,1c008286 <pos_fll_init+0x84>
1c0082c4:	1a1006b7          	lui	a3,0x1a100
1c0082c8:	2106f703          	p.lw	a4,a6(a3)
1c0082cc:	00f35313          	srli	t1,t1,0xf
1c0082d0:	de032733          	p.insert	a4,t1,15,0
1c0082d4:	c7af2733          	p.insert	a4,t5,3,26
1c0082d8:	00e6e823          	p.sw	a4,a6(a3)
1c0082dc:	4705                	li	a4,1
1c0082de:	00e7c5a3          	p.sb	a4,a1(a5)
1c0082e2:	8082                	ret
1c0082e4:	fff70793          	addi	a5,a4,-1
1c0082e8:	4e05                	li	t3,1
1c0082ea:	00fe1e33          	sll	t3,t3,a5
1c0082ee:	00170f13          	addi	t5,a4,1
1c0082f2:	b77d                	j	1c0082a0 <pos_fll_init+0x9e>

1c0082f4 <pos_fll_constructor>:
1c0082f4:	1c0016b7          	lui	a3,0x1c001
1c0082f8:	1c0017b7          	lui	a5,0x1c001
1c0082fc:	87c68713          	addi	a4,a3,-1924 # 1c00087c <pos_fll_freq>
1c008300:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c008304:	8606ae23          	sw	zero,-1924(a3)
1c008308:	00072223          	sw	zero,4(a4)
1c00830c:	00072423          	sw	zero,8(a4)
1c008310:	00079023          	sh	zero,0(a5)
1c008314:	00078123          	sb	zero,2(a5)
1c008318:	8082                	ret

1c00831a <pos_soc_init>:
1c00831a:	1141                	addi	sp,sp,-16
1c00831c:	c606                	sw	ra,12(sp)
1c00831e:	c422                	sw	s0,8(sp)
1c008320:	3fd1                	jal	1c0082f4 <pos_fll_constructor>
1c008322:	4501                	li	a0,0
1c008324:	3df9                	jal	1c008202 <pos_fll_init>
1c008326:	1c001437          	lui	s0,0x1c001
1c00832a:	88a42423          	sw	a0,-1912(s0) # 1c000888 <pos_freq_domains>
1c00832e:	4505                	li	a0,1
1c008330:	3dc9                	jal	1c008202 <pos_fll_init>
1c008332:	88840413          	addi	s0,s0,-1912
1c008336:	c408                	sw	a0,8(s0)
1c008338:	4509                	li	a0,2
1c00833a:	35e1                	jal	1c008202 <pos_fll_init>
1c00833c:	c048                	sw	a0,4(s0)
1c00833e:	40b2                	lw	ra,12(sp)
1c008340:	4422                	lw	s0,8(sp)
1c008342:	0141                	addi	sp,sp,16
1c008344:	8082                	ret

1c008346 <pos_wait_forever>:
1c008346:	f14027f3          	csrr	a5,mhartid
1c00834a:	477d                	li	a4,31
1c00834c:	ca5797b3          	p.extractu	a5,a5,5,5
1c008350:	00e78963          	beq	a5,a4,1c008362 <pos_wait_forever+0x1c>
1c008354:	002047b7          	lui	a5,0x204
1c008358:	577d                	li	a4,-1
1c00835a:	c3d8                	sw	a4,4(a5)
1c00835c:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c008360:	a001                	j	1c008360 <pos_wait_forever+0x1a>
1c008362:	1a10a7b7          	lui	a5,0x1a10a
1c008366:	577d                	li	a4,-1
1c008368:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c00836c:	10500073          	wfi
1c008370:	10500073          	wfi
1c008374:	bfe5                	j	1c00836c <pos_wait_forever+0x26>

1c008376 <memcpy>:
1c008376:	00a5e7b3          	or	a5,a1,a0
1c00837a:	fa27b7b3          	p.bclr	a5,a5,29,2
1c00837e:	882a                	mv	a6,a0
1c008380:	10078163          	beqz	a5,1c008482 <memcpy+0x10c>
1c008384:	12060263          	beqz	a2,1c0084a8 <memcpy+0x132>
1c008388:	00458793          	addi	a5,a1,4
1c00838c:	00450693          	addi	a3,a0,4 # 1a100004 <__l2_shared_end+0xa0ffffc>
1c008390:	04a7b7b3          	p.sletu	a5,a5,a0
1c008394:	04b6b6b3          	p.sletu	a3,a3,a1
1c008398:	873e                	mv	a4,a5
1c00839a:	87b6                	mv	a5,a3
1c00839c:	8fd9                	or	a5,a5,a4
1c00839e:	0ff7f793          	andi	a5,a5,255
1c0083a2:	cbe9                	beqz	a5,1c008474 <memcpy+0xfe>
1c0083a4:	00863793          	sltiu	a5,a2,8
1c0083a8:	0017c793          	xori	a5,a5,1
1c0083ac:	0ff7f793          	andi	a5,a5,255
1c0083b0:	c3f1                	beqz	a5,1c008474 <memcpy+0xfe>
1c0083b2:	40b007b3          	neg	a5,a1
1c0083b6:	fa27b7b3          	p.bclr	a5,a5,29,2
1c0083ba:	fff60313          	addi	t1,a2,-1
1c0083be:	c3ed                	beqz	a5,1c0084a0 <memcpy+0x12a>
1c0083c0:	0005c703          	lbu	a4,0(a1)
1c0083c4:	00158893          	addi	a7,a1,1
1c0083c8:	00150813          	addi	a6,a0,1
1c0083cc:	00e50023          	sb	a4,0(a0)
1c0083d0:	0217a863          	p.beqimm	a5,1,1c008400 <memcpy+0x8a>
1c0083d4:	0015c703          	lbu	a4,1(a1)
1c0083d8:	00258893          	addi	a7,a1,2
1c0083dc:	00250813          	addi	a6,a0,2
1c0083e0:	00e500a3          	sb	a4,1(a0)
1c0083e4:	ffe60313          	addi	t1,a2,-2
1c0083e8:	0037bc63          	p.bneimm	a5,3,1c008400 <memcpy+0x8a>
1c0083ec:	0025c703          	lbu	a4,2(a1)
1c0083f0:	00358893          	addi	a7,a1,3
1c0083f4:	00350813          	addi	a6,a0,3
1c0083f8:	00e50123          	sb	a4,2(a0)
1c0083fc:	ffd60313          	addi	t1,a2,-3
1c008400:	8e1d                	sub	a2,a2,a5
1c008402:	00265713          	srli	a4,a2,0x2
1c008406:	00f506b3          	add	a3,a0,a5
1c00840a:	95be                	add	a1,a1,a5
1c00840c:	cf59                	beqz	a4,1c0084aa <memcpy+0x134>
1c00840e:	004740fb          	lp.setup	x1,a4,1c008416 <memcpy+0xa0>
1c008412:	0045a78b          	p.lw	a5,4(a1!)
1c008416:	00f6a22b          	p.sw	a5,4(a3!)
1c00841a:	c20635b3          	p.bclr	a1,a2,1,0
1c00841e:	40b306b3          	sub	a3,t1,a1
1c008422:	00b807b3          	add	a5,a6,a1
1c008426:	00b88733          	add	a4,a7,a1
1c00842a:	04b60b63          	beq	a2,a1,1c008480 <memcpy+0x10a>
1c00842e:	00074603          	lbu	a2,0(a4)
1c008432:	00c78023          	sb	a2,0(a5)
1c008436:	0416a563          	p.beqimm	a3,1,1c008480 <memcpy+0x10a>
1c00843a:	00174603          	lbu	a2,1(a4)
1c00843e:	00c780a3          	sb	a2,1(a5)
1c008442:	0226af63          	p.beqimm	a3,2,1c008480 <memcpy+0x10a>
1c008446:	00274603          	lbu	a2,2(a4)
1c00844a:	00c78123          	sb	a2,2(a5)
1c00844e:	0236a963          	p.beqimm	a3,3,1c008480 <memcpy+0x10a>
1c008452:	00374603          	lbu	a2,3(a4)
1c008456:	00c781a3          	sb	a2,3(a5)
1c00845a:	0246a363          	p.beqimm	a3,4,1c008480 <memcpy+0x10a>
1c00845e:	00474603          	lbu	a2,4(a4)
1c008462:	00c78223          	sb	a2,4(a5)
1c008466:	0056ad63          	p.beqimm	a3,5,1c008480 <memcpy+0x10a>
1c00846a:	00574703          	lbu	a4,5(a4)
1c00846e:	00e782a3          	sb	a4,5(a5)
1c008472:	8082                	ret
1c008474:	004640fb          	lp.setup	x1,a2,1c00847c <memcpy+0x106>
1c008478:	0015c78b          	p.lbu	a5,1(a1!)
1c00847c:	00f800ab          	p.sb	a5,1(a6!)
1c008480:	8082                	ret
1c008482:	fa2637b3          	p.bclr	a5,a2,29,2
1c008486:	f389                	bnez	a5,1c008388 <memcpy+0x12>
1c008488:	de65                	beqz	a2,1c008480 <memcpy+0x10a>
1c00848a:	ffc60793          	addi	a5,a2,-4
1c00848e:	8389                	srli	a5,a5,0x2
1c008490:	0785                	addi	a5,a5,1
1c008492:	0047c0fb          	lp.setup	x1,a5,1c00849a <memcpy+0x124>
1c008496:	0045a70b          	p.lw	a4,4(a1!)
1c00849a:	00e8222b          	p.sw	a4,4(a6!)
1c00849e:	8082                	ret
1c0084a0:	88ae                	mv	a7,a1
1c0084a2:	882a                	mv	a6,a0
1c0084a4:	8332                	mv	t1,a2
1c0084a6:	bfa9                	j	1c008400 <memcpy+0x8a>
1c0084a8:	8082                	ret
1c0084aa:	4705                	li	a4,1
1c0084ac:	b78d                	j	1c00840e <memcpy+0x98>

1c0084ae <memmove>:
1c0084ae:	40b507b3          	sub	a5,a0,a1
1c0084b2:	0ec7ec63          	bltu	a5,a2,1c0085aa <memmove+0xfc>
1c0084b6:	20060463          	beqz	a2,1c0086be <memmove+0x210>
1c0084ba:	00450793          	addi	a5,a0,4
1c0084be:	00458693          	addi	a3,a1,4
1c0084c2:	04b7b7b3          	p.sletu	a5,a5,a1
1c0084c6:	04a6b6b3          	p.sletu	a3,a3,a0
1c0084ca:	873e                	mv	a4,a5
1c0084cc:	87b6                	mv	a5,a3
1c0084ce:	8fd9                	or	a5,a5,a4
1c0084d0:	0ff7f793          	andi	a5,a5,255
1c0084d4:	1c078d63          	beqz	a5,1c0086ae <memmove+0x200>
1c0084d8:	00863793          	sltiu	a5,a2,8
1c0084dc:	0017c793          	xori	a5,a5,1
1c0084e0:	0ff7f793          	andi	a5,a5,255
1c0084e4:	1c078563          	beqz	a5,1c0086ae <memmove+0x200>
1c0084e8:	40b007b3          	neg	a5,a1
1c0084ec:	fa27b7b3          	p.bclr	a5,a5,29,2
1c0084f0:	fff60313          	addi	t1,a2,-1
1c0084f4:	88ae                	mv	a7,a1
1c0084f6:	1e078363          	beqz	a5,1c0086dc <memmove+0x22e>
1c0084fa:	0018c70b          	p.lbu	a4,1(a7!)
1c0084fe:	882a                	mv	a6,a0
1c008500:	00e800ab          	p.sb	a4,1(a6!)
1c008504:	0217a863          	p.beqimm	a5,1,1c008534 <memmove+0x86>
1c008508:	0015c703          	lbu	a4,1(a1)
1c00850c:	00250813          	addi	a6,a0,2
1c008510:	00258893          	addi	a7,a1,2
1c008514:	00e500a3          	sb	a4,1(a0)
1c008518:	ffe60313          	addi	t1,a2,-2
1c00851c:	0037bc63          	p.bneimm	a5,3,1c008534 <memmove+0x86>
1c008520:	0025c703          	lbu	a4,2(a1)
1c008524:	00350813          	addi	a6,a0,3
1c008528:	00358893          	addi	a7,a1,3
1c00852c:	00e50123          	sb	a4,2(a0)
1c008530:	ffd60313          	addi	t1,a2,-3
1c008534:	8e1d                	sub	a2,a2,a5
1c008536:	00265713          	srli	a4,a2,0x2
1c00853a:	00f506b3          	add	a3,a0,a5
1c00853e:	95be                	add	a1,a1,a5
1c008540:	1a070363          	beqz	a4,1c0086e6 <memmove+0x238>
1c008544:	004740fb          	lp.setup	x1,a4,1c00854c <memmove+0x9e>
1c008548:	0045a78b          	p.lw	a5,4(a1!)
1c00854c:	00f6a22b          	p.sw	a5,4(a3!)
1c008550:	c20635b3          	p.bclr	a1,a2,1,0
1c008554:	40b306b3          	sub	a3,t1,a1
1c008558:	00b807b3          	add	a5,a6,a1
1c00855c:	00b88733          	add	a4,a7,a1
1c008560:	14b60e63          	beq	a2,a1,1c0086bc <memmove+0x20e>
1c008564:	00074603          	lbu	a2,0(a4)
1c008568:	00c78023          	sb	a2,0(a5)
1c00856c:	1416a863          	p.beqimm	a3,1,1c0086bc <memmove+0x20e>
1c008570:	00174603          	lbu	a2,1(a4)
1c008574:	00c780a3          	sb	a2,1(a5)
1c008578:	1426a263          	p.beqimm	a3,2,1c0086bc <memmove+0x20e>
1c00857c:	00274603          	lbu	a2,2(a4)
1c008580:	00c78123          	sb	a2,2(a5)
1c008584:	1236ac63          	p.beqimm	a3,3,1c0086bc <memmove+0x20e>
1c008588:	00374603          	lbu	a2,3(a4)
1c00858c:	00c781a3          	sb	a2,3(a5)
1c008590:	1246a663          	p.beqimm	a3,4,1c0086bc <memmove+0x20e>
1c008594:	00474603          	lbu	a2,4(a4)
1c008598:	00c78223          	sb	a2,4(a5)
1c00859c:	1256a063          	p.beqimm	a3,5,1c0086bc <memmove+0x20e>
1c0085a0:	00574703          	lbu	a4,5(a4)
1c0085a4:	00e782a3          	sb	a4,5(a5)
1c0085a8:	8082                	ret
1c0085aa:	ffc60793          	addi	a5,a2,-4
1c0085ae:	00f50833          	add	a6,a0,a5
1c0085b2:	00f58333          	add	t1,a1,a5
1c0085b6:	00c58733          	add	a4,a1,a2
1c0085ba:	00c508b3          	add	a7,a0,a2
1c0085be:	05073733          	p.sletu	a4,a4,a6
1c0085c2:	0468b833          	p.sletu	a6,a7,t1
1c0085c6:	86ba                	mv	a3,a4
1c0085c8:	8742                	mv	a4,a6
1c0085ca:	8f55                	or	a4,a4,a3
1c0085cc:	0ff77713          	andi	a4,a4,255
1c0085d0:	cb65                	beqz	a4,1c0086c0 <memmove+0x212>
1c0085d2:	00863713          	sltiu	a4,a2,8
1c0085d6:	00174713          	xori	a4,a4,1
1c0085da:	0ff77713          	andi	a4,a4,255
1c0085de:	c36d                	beqz	a4,1c0086c0 <memmove+0x212>
1c0085e0:	fa233733          	p.bclr	a4,t1,29,2
1c0085e4:	fff60893          	addi	a7,a2,-1
1c0085e8:	cb65                	beqz	a4,1c0086d8 <memmove+0x22a>
1c0085ea:	011586b3          	add	a3,a1,a7
1c0085ee:	0006c683          	lbu	a3,0(a3)
1c0085f2:	00d548a3          	p.sb	a3,a7(a0)
1c0085f6:	02172463          	p.beqimm	a4,1,1c00861e <memmove+0x170>
1c0085fa:	ffe60893          	addi	a7,a2,-2
1c0085fe:	011586b3          	add	a3,a1,a7
1c008602:	0006c683          	lbu	a3,0(a3)
1c008606:	00d548a3          	p.sb	a3,a7(a0)
1c00860a:	00373a63          	p.bneimm	a4,3,1c00861e <memmove+0x170>
1c00860e:	ffd60893          	addi	a7,a2,-3
1c008612:	011586b3          	add	a3,a1,a7
1c008616:	0006c683          	lbu	a3,0(a3)
1c00861a:	00d548a3          	p.sb	a3,a7(a0)
1c00861e:	8e19                	sub	a2,a2,a4
1c008620:	8f99                	sub	a5,a5,a4
1c008622:	00265713          	srli	a4,a2,0x2
1c008626:	00f506b3          	add	a3,a0,a5
1c00862a:	97ae                	add	a5,a5,a1
1c00862c:	cb5d                	beqz	a4,1c0086e2 <memmove+0x234>
1c00862e:	004740fb          	lp.setup	x1,a4,1c008636 <memmove+0x188>
1c008632:	ffc7a80b          	p.lw	a6,-4(a5!)
1c008636:	ff06ae2b          	p.sw	a6,-4(a3!)
1c00863a:	c20637b3          	p.bclr	a5,a2,1,0
1c00863e:	40f888b3          	sub	a7,a7,a5
1c008642:	06f60d63          	beq	a2,a5,1c0086bc <memmove+0x20e>
1c008646:	fff88793          	addi	a5,a7,-1
1c00864a:	00f58733          	add	a4,a1,a5
1c00864e:	00074703          	lbu	a4,0(a4)
1c008652:	00e547a3          	p.sb	a4,a5(a0)
1c008656:	c3bd                	beqz	a5,1c0086bc <memmove+0x20e>
1c008658:	ffe88793          	addi	a5,a7,-2
1c00865c:	00f58733          	add	a4,a1,a5
1c008660:	00074703          	lbu	a4,0(a4)
1c008664:	00e547a3          	p.sb	a4,a5(a0)
1c008668:	cbb1                	beqz	a5,1c0086bc <memmove+0x20e>
1c00866a:	ffd88793          	addi	a5,a7,-3
1c00866e:	00f58733          	add	a4,a1,a5
1c008672:	00074703          	lbu	a4,0(a4)
1c008676:	00e547a3          	p.sb	a4,a5(a0)
1c00867a:	c3a9                	beqz	a5,1c0086bc <memmove+0x20e>
1c00867c:	ffc88793          	addi	a5,a7,-4
1c008680:	00f58733          	add	a4,a1,a5
1c008684:	00074703          	lbu	a4,0(a4)
1c008688:	00e547a3          	p.sb	a4,a5(a0)
1c00868c:	cb85                	beqz	a5,1c0086bc <memmove+0x20e>
1c00868e:	ffb88793          	addi	a5,a7,-5
1c008692:	00f58733          	add	a4,a1,a5
1c008696:	00074703          	lbu	a4,0(a4)
1c00869a:	00e547a3          	p.sb	a4,a5(a0)
1c00869e:	cf99                	beqz	a5,1c0086bc <memmove+0x20e>
1c0086a0:	18e9                	addi	a7,a7,-6
1c0086a2:	95c6                	add	a1,a1,a7
1c0086a4:	0005c783          	lbu	a5,0(a1)
1c0086a8:	00f548a3          	p.sb	a5,a7(a0)
1c0086ac:	8082                	ret
1c0086ae:	87aa                	mv	a5,a0
1c0086b0:	004640fb          	lp.setup	x1,a2,1c0086b8 <memmove+0x20a>
1c0086b4:	0015c70b          	p.lbu	a4,1(a1!)
1c0086b8:	00e780ab          	p.sb	a4,1(a5!)
1c0086bc:	8082                	ret
1c0086be:	8082                	ret
1c0086c0:	167d                	addi	a2,a2,-1
1c0086c2:	00c507b3          	add	a5,a0,a2
1c0086c6:	95b2                	add	a1,a1,a2
1c0086c8:	0605                	addi	a2,a2,1
1c0086ca:	004640fb          	lp.setup	x1,a2,1c0086d2 <memmove+0x224>
1c0086ce:	fff5c70b          	p.lbu	a4,-1(a1!)
1c0086d2:	fee78fab          	p.sb	a4,-1(a5!)
1c0086d6:	8082                	ret
1c0086d8:	88b2                	mv	a7,a2
1c0086da:	b791                	j	1c00861e <memmove+0x170>
1c0086dc:	882a                	mv	a6,a0
1c0086de:	8332                	mv	t1,a2
1c0086e0:	bd91                	j	1c008534 <memmove+0x86>
1c0086e2:	4705                	li	a4,1
1c0086e4:	b7a9                	j	1c00862e <memmove+0x180>
1c0086e6:	4705                	li	a4,1
1c0086e8:	bdb1                	j	1c008544 <memmove+0x96>

1c0086ea <strchr>:
1c0086ea:	00054783          	lbu	a5,0(a0)
1c0086ee:	0ff5f593          	andi	a1,a1,255
1c0086f2:	00b78c63          	beq	a5,a1,1c00870a <strchr+0x20>
1c0086f6:	cb99                	beqz	a5,1c00870c <strchr+0x22>
1c0086f8:	00150793          	addi	a5,a0,1
1c0086fc:	a011                	j	1c008700 <strchr+0x16>
1c0086fe:	c719                	beqz	a4,1c00870c <strchr+0x22>
1c008700:	853e                	mv	a0,a5
1c008702:	0017c70b          	p.lbu	a4,1(a5!)
1c008706:	feb71ce3          	bne	a4,a1,1c0086fe <strchr+0x14>
1c00870a:	8082                	ret
1c00870c:	0015b593          	seqz	a1,a1
1c008710:	40b005b3          	neg	a1,a1
1c008714:	8d6d                	and	a0,a0,a1
1c008716:	8082                	ret

1c008718 <pos_libc_fputc_locked>:
1c008718:	6689                	lui	a3,0x2
1c00871a:	f14027f3          	csrr	a5,mhartid
1c00871e:	f8068693          	addi	a3,a3,-128 # 1f80 <__cluster_text_size+0x1f80>
1c008722:	00379713          	slli	a4,a5,0x3
1c008726:	078a                	slli	a5,a5,0x2
1c008728:	8ff5                	and	a5,a5,a3
1c00872a:	ee873733          	p.bclr	a4,a4,23,8
1c00872e:	1a10f6b7          	lui	a3,0x1a10f
1c008732:	0ff57513          	andi	a0,a0,255
1c008736:	9736                	add	a4,a4,a3
1c008738:	00a7e723          	p.sw	a0,a4(a5)
1c00873c:	4501                	li	a0,0
1c00873e:	8082                	ret

1c008740 <pos_libc_prf_locked>:
1c008740:	a0a9                	j	1c00878a <pos_libc_prf>

1c008742 <exit>:
1c008742:	1141                	addi	sp,sp,-16
1c008744:	c606                	sw	ra,12(sp)
1c008746:	1a1047b7          	lui	a5,0x1a104
1c00874a:	c1f54533          	p.bset	a0,a0,0,31
1c00874e:	0aa7a023          	sw	a0,160(a5) # 1a1040a0 <__l2_shared_end+0xa104098>
1c008752:	3ed5                	jal	1c008346 <pos_wait_forever>

1c008754 <pos_io_start>:
1c008754:	4501                	li	a0,0
1c008756:	8082                	ret

1c008758 <pos_io_stop>:
1c008758:	4501                	li	a0,0
1c00875a:	8082                	ret

1c00875c <printf>:
1c00875c:	7139                	addi	sp,sp,-64
1c00875e:	02410313          	addi	t1,sp,36
1c008762:	d432                	sw	a2,40(sp)
1c008764:	862a                	mv	a2,a0
1c008766:	1c008537          	lui	a0,0x1c008
1c00876a:	d22e                	sw	a1,36(sp)
1c00876c:	d636                	sw	a3,44(sp)
1c00876e:	4589                	li	a1,2
1c008770:	869a                	mv	a3,t1
1c008772:	71850513          	addi	a0,a0,1816 # 1c008718 <pos_libc_fputc_locked>
1c008776:	ce06                	sw	ra,28(sp)
1c008778:	d83a                	sw	a4,48(sp)
1c00877a:	da3e                	sw	a5,52(sp)
1c00877c:	dc42                	sw	a6,56(sp)
1c00877e:	de46                	sw	a7,60(sp)
1c008780:	c61a                	sw	t1,12(sp)
1c008782:	3f7d                	jal	1c008740 <pos_libc_prf_locked>
1c008784:	40f2                	lw	ra,28(sp)
1c008786:	6121                	addi	sp,sp,64
1c008788:	8082                	ret

1c00878a <pos_libc_prf>:
1c00878a:	7169                	addi	sp,sp,-304
1c00878c:	12812423          	sw	s0,296(sp)
1c008790:	4401                	li	s0,0
1c008792:	11612823          	sw	s6,272(sp)
1c008796:	11712623          	sw	s7,268(sp)
1c00879a:	11812423          	sw	s8,264(sp)
1c00879e:	11912223          	sw	s9,260(sp)
1c0087a2:	11a12023          	sw	s10,256(sp)
1c0087a6:	dfee                	sw	s11,252(sp)
1c0087a8:	12112623          	sw	ra,300(sp)
1c0087ac:	8da2                	mv	s11,s0
1c0087ae:	12912223          	sw	s1,292(sp)
1c0087b2:	13212023          	sw	s2,288(sp)
1c0087b6:	11312e23          	sw	s3,284(sp)
1c0087ba:	11412c23          	sw	s4,280(sp)
1c0087be:	11512a23          	sw	s5,276(sp)
1c0087c2:	8b2a                	mv	s6,a0
1c0087c4:	8d2e                	mv	s10,a1
1c0087c6:	8c36                	mv	s8,a3
1c0087c8:	1c000bb7          	lui	s7,0x1c000
1c0087cc:	02410c93          	addi	s9,sp,36
1c0087d0:	8432                	mv	s0,a2
1c0087d2:	00044503          	lbu	a0,0(s0)
1c0087d6:	0405                	addi	s0,s0,1
1c0087d8:	cd11                	beqz	a0,1c0087f4 <pos_libc_prf+0x6a>
1c0087da:	02500793          	li	a5,37
1c0087de:	04f50863          	beq	a0,a5,1c00882e <pos_libc_prf+0xa4>
1c0087e2:	85ea                	mv	a1,s10
1c0087e4:	9b02                	jalr	s6
1c0087e6:	31f52563          	p.beqimm	a0,-1,1c008af0 <pos_libc_prf+0x366>
1c0087ea:	0d85                	addi	s11,s11,1
1c0087ec:	00044503          	lbu	a0,0(s0)
1c0087f0:	0405                	addi	s0,s0,1
1c0087f2:	f565                	bnez	a0,1c0087da <pos_libc_prf+0x50>
1c0087f4:	846e                	mv	s0,s11
1c0087f6:	8522                	mv	a0,s0
1c0087f8:	12c12083          	lw	ra,300(sp)
1c0087fc:	12812403          	lw	s0,296(sp)
1c008800:	12412483          	lw	s1,292(sp)
1c008804:	12012903          	lw	s2,288(sp)
1c008808:	11c12983          	lw	s3,284(sp)
1c00880c:	11812a03          	lw	s4,280(sp)
1c008810:	11412a83          	lw	s5,276(sp)
1c008814:	11012b03          	lw	s6,272(sp)
1c008818:	10c12b83          	lw	s7,268(sp)
1c00881c:	10812c03          	lw	s8,264(sp)
1c008820:	10412c83          	lw	s9,260(sp)
1c008824:	10012d03          	lw	s10,256(sp)
1c008828:	5dfe                	lw	s11,252(sp)
1c00882a:	6155                	addi	sp,sp,304
1c00882c:	8082                	ret
1c00882e:	00044483          	lbu	s1,0(s0)
1c008832:	02000693          	li	a3,32
1c008836:	00140a93          	addi	s5,s0,1
1c00883a:	054b8513          	addi	a0,s7,84 # 1c000054 <__DTOR_END__+0x38>
1c00883e:	85a6                	mv	a1,s1
1c008840:	c836                	sw	a3,16(sp)
1c008842:	cc02                	sw	zero,24(sp)
1c008844:	ca02                	sw	zero,20(sp)
1c008846:	ce02                	sw	zero,28(sp)
1c008848:	c602                	sw	zero,12(sp)
1c00884a:	02300913          	li	s2,35
1c00884e:	02d00a13          	li	s4,45
1c008852:	89d6                	mv	s3,s5
1c008854:	3d59                	jal	1c0086ea <strchr>
1c008856:	c915                	beqz	a0,1c00888a <pos_libc_prf+0x100>
1c008858:	2b248b63          	beq	s1,s2,1c008b0e <pos_libc_prf+0x384>
1c00885c:	0c997463          	bleu	s1,s2,1c008924 <pos_libc_prf+0x19a>
1c008860:	2b448363          	beq	s1,s4,1c008b06 <pos_libc_prf+0x37c>
1c008864:	03000613          	li	a2,48
1c008868:	28c48a63          	beq	s1,a2,1c008afc <pos_libc_prf+0x372>
1c00886c:	02b00693          	li	a3,43
1c008870:	28d48263          	beq	s1,a3,1c008af4 <pos_libc_prf+0x36a>
1c008874:	8456                	mv	s0,s5
1c008876:	00044483          	lbu	s1,0(s0)
1c00887a:	00140a93          	addi	s5,s0,1
1c00887e:	054b8513          	addi	a0,s7,84
1c008882:	85a6                	mv	a1,s1
1c008884:	89d6                	mv	s3,s5
1c008886:	3595                	jal	1c0086ea <strchr>
1c008888:	f961                	bnez	a0,1c008858 <pos_libc_prf+0xce>
1c00888a:	02a00613          	li	a2,42
1c00888e:	2ac48663          	beq	s1,a2,1c008b3a <pos_libc_prf+0x3b0>
1c008892:	fd048613          	addi	a2,s1,-48
1c008896:	45a5                	li	a1,9
1c008898:	4901                	li	s2,0
1c00889a:	28c5f063          	bleu	a2,a1,1c008b1a <pos_libc_prf+0x390>
1c00889e:	02e00693          	li	a3,46
1c0088a2:	5a7d                	li	s4,-1
1c0088a4:	2ed48363          	beq	s1,a3,1c008b8a <pos_libc_prf+0x400>
1c0088a8:	1c0007b7          	lui	a5,0x1c000
1c0088ac:	85a6                	mv	a1,s1
1c0088ae:	05c78513          	addi	a0,a5,92 # 1c00005c <__DTOR_END__+0x40>
1c0088b2:	3d25                	jal	1c0086ea <strchr>
1c0088b4:	844e                	mv	s0,s3
1c0088b6:	c509                	beqz	a0,1c0088c0 <pos_libc_prf+0x136>
1c0088b8:	0009c483          	lbu	s1,0(s3)
1c0088bc:	00198413          	addi	s0,s3,1
1c0088c0:	06700693          	li	a3,103
1c0088c4:	2896d963          	ble	s1,a3,1c008b56 <pos_libc_prf+0x3cc>
1c0088c8:	07000693          	li	a3,112
1c0088cc:	7cd48b63          	beq	s1,a3,1c0090a2 <pos_libc_prf+0x918>
1c0088d0:	2e96d163          	ble	s1,a3,1c008bb2 <pos_libc_prf+0x428>
1c0088d4:	07500693          	li	a3,117
1c0088d8:	12d489e3          	beq	s1,a3,1c00920a <pos_libc_prf+0xa80>
1c0088dc:	07800693          	li	a3,120
1c0088e0:	06d48663          	beq	s1,a3,1c00894c <pos_libc_prf+0x1c2>
1c0088e4:	07300693          	li	a3,115
1c0088e8:	18d49fe3          	bne	s1,a3,1c009286 <pos_libc_prf+0xafc>
1c0088ec:	000c2583          	lw	a1,0(s8)
1c0088f0:	004c0993          	addi	s3,s8,4
1c0088f4:	4481                	li	s1,0
1c0088f6:	86ae                	mv	a3,a1
1c0088f8:	0c8350fb          	lp.setupi	x1,200,1c008904 <pos_libc_prf+0x17a>
1c0088fc:	0016c70b          	p.lbu	a4,1(a3!) # 1a10f001 <__l2_shared_end+0xa10eff9>
1c008900:	18070ae3          	beqz	a4,1c009294 <pos_libc_prf+0xb0a>
1c008904:	0485                	addi	s1,s1,1
1c008906:	000a4763          	bltz	s4,1c008914 <pos_libc_prf+0x18a>
1c00890a:	0544c4b3          	p.min	s1,s1,s4
1c00890e:	8c4e                	mv	s8,s3
1c008910:	ec0481e3          	beqz	s1,1c0087d2 <pos_libc_prf+0x48>
1c008914:	8626                	mv	a2,s1
1c008916:	8566                	mv	a0,s9
1c008918:	3cb9                	jal	1c008376 <memcpy>
1c00891a:	8c4e                	mv	s8,s3
1c00891c:	1b24db63          	ble	s2,s1,1c008ad2 <pos_libc_prf+0x348>
1c008920:	c602                	sw	zero,12(sp)
1c008922:	a0f9                	j	1c0089f0 <pos_libc_prf+0x266>
1c008924:	ec0488e3          	beqz	s1,1c0087f4 <pos_libc_prf+0x6a>
1c008928:	02000593          	li	a1,32
1c00892c:	f4b494e3          	bne	s1,a1,1c008874 <pos_libc_prf+0xea>
1c008930:	4785                	li	a5,1
1c008932:	cc3e                	sw	a5,24(sp)
1c008934:	8456                	mv	s0,s5
1c008936:	b781                	j	1c008876 <pos_libc_prf+0xec>
1c008938:	06300693          	li	a3,99
1c00893c:	0ad48de3          	beq	s1,a3,1c0091f6 <pos_libc_prf+0xa6c>
1c008940:	0096cde3          	blt	a3,s1,1c00915a <pos_libc_prf+0x9d0>
1c008944:	05800693          	li	a3,88
1c008948:	12d49fe3          	bne	s1,a3,1c009286 <pos_libc_prf+0xafc>
1c00894c:	47b2                	lw	a5,12(sp)
1c00894e:	004c0893          	addi	a7,s8,4
1c008952:	000c2503          	lw	a0,0(s8)
1c008956:	260788e3          	beqz	a5,1c0093c6 <pos_libc_prf+0xc3c>
1c00895a:	76e1                	lui	a3,0xffff8
1c00895c:	8306c693          	xori	a3,a3,-2000
1c008960:	02d11223          	sh	a3,36(sp)
1c008964:	4309                	li	t1,2
1c008966:	02610613          	addi	a2,sp,38
1c00896a:	86b2                	mv	a3,a2
1c00896c:	4ea5                	li	t4,9
1c00896e:	f6453733          	p.bclr	a4,a0,27,4
1c008972:	0ff77793          	andi	a5,a4,255
1c008976:	03078593          	addi	a1,a5,48
1c00897a:	8111                	srli	a0,a0,0x4
1c00897c:	05778793          	addi	a5,a5,87
1c008980:	70eee963          	bltu	t4,a4,1c009092 <pos_libc_prf+0x908>
1c008984:	00b680ab          	p.sb	a1,1(a3!) # ffff8001 <pulp__FC+0xffff8002>
1c008988:	f17d                	bnez	a0,1c00896e <pos_libc_prf+0x1e4>
1c00898a:	40c68733          	sub	a4,a3,a2
1c00898e:	01475d63          	ble	s4,a4,1c0089a8 <pos_libc_prf+0x21e>
1c008992:	40d605b3          	sub	a1,a2,a3
1c008996:	03000513          	li	a0,48
1c00899a:	95d2                	add	a1,a1,s4
1c00899c:	0045c0fb          	lp.setup	x1,a1,1c0089a4 <pos_libc_prf+0x21a>
1c0089a0:	00a680ab          	p.sb	a0,1(a3!)
1c0089a4:	40c68733          	sub	a4,a3,a2
1c0089a8:	fe068fab          	p.sb	zero,-1(a3!)
1c0089ac:	00d67c63          	bleu	a3,a2,1c0089c4 <pos_libc_prf+0x23a>
1c0089b0:	00064583          	lbu	a1,0(a2)
1c0089b4:	0006c783          	lbu	a5,0(a3)
1c0089b8:	feb68fab          	p.sb	a1,-1(a3!)
1c0089bc:	00f600ab          	p.sb	a5,1(a2!)
1c0089c0:	fed668e3          	bltu	a2,a3,1c0089b0 <pos_libc_prf+0x226>
1c0089c4:	05800693          	li	a3,88
1c0089c8:	20d483e3          	beq	s1,a3,1c0093ce <pos_libc_prf+0xc44>
1c0089cc:	46b2                	lw	a3,12(sp)
1c0089ce:	006704b3          	add	s1,a4,t1
1c0089d2:	c299                	beqz	a3,1c0089d8 <pos_libc_prf+0x24e>
1c0089d4:	4709                	li	a4,2
1c0089d6:	c63a                	sw	a4,12(sp)
1c0089d8:	0c800793          	li	a5,200
1c0089dc:	23fa24e3          	p.beqimm	s4,-1,1c009404 <pos_libc_prf+0xc7a>
1c0089e0:	1097c863          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c0089e4:	02000793          	li	a5,32
1c0089e8:	8c46                	mv	s8,a7
1c0089ea:	c83e                	sw	a5,16(sp)
1c0089ec:	0f24d163          	ble	s2,s1,1c008ace <pos_libc_prf+0x344>
1c0089f0:	4772                	lw	a4,28(sp)
1c0089f2:	0c0702e3          	beqz	a4,1c0092b6 <pos_libc_prf+0xb2c>
1c0089f6:	009c87b3          	add	a5,s9,s1
1c0089fa:	40f007b3          	neg	a5,a5
1c0089fe:	fa27b7b3          	p.bclr	a5,a5,29,2
1c008a02:	4595                	li	a1,5
1c008a04:	00378613          	addi	a2,a5,3
1c008a08:	fff90693          	addi	a3,s2,-1
1c008a0c:	04b67633          	p.maxu	a2,a2,a1
1c008a10:	8e85                	sub	a3,a3,s1
1c008a12:	409905b3          	sub	a1,s2,s1
1c008a16:	06c6e163          	bltu	a3,a2,1c008a78 <pos_libc_prf+0x2ee>
1c008a1a:	8626                	mv	a2,s1
1c008a1c:	cb85                	beqz	a5,1c008a4c <pos_libc_prf+0x2c2>
1c008a1e:	1998                	addi	a4,sp,240
1c008a20:	00970633          	add	a2,a4,s1
1c008a24:	02000693          	li	a3,32
1c008a28:	f2d60a23          	sb	a3,-204(a2)
1c008a2c:	00148613          	addi	a2,s1,1
1c008a30:	0017ae63          	p.beqimm	a5,1,1c008a4c <pos_libc_prf+0x2c2>
1c008a34:	963a                	add	a2,a2,a4
1c008a36:	f2d60a23          	sb	a3,-204(a2)
1c008a3a:	00248613          	addi	a2,s1,2
1c008a3e:	0037b763          	p.bneimm	a5,3,1c008a4c <pos_libc_prf+0x2c2>
1c008a42:	963a                	add	a2,a2,a4
1c008a44:	f2d60a23          	sb	a3,-204(a2)
1c008a48:	00348613          	addi	a2,s1,3
1c008a4c:	8d9d                	sub	a1,a1,a5
1c008a4e:	0025d693          	srli	a3,a1,0x2
1c008a52:	97a6                	add	a5,a5,s1
1c008a54:	97e6                	add	a5,a5,s9
1c008a56:	42068fe3          	beqz	a3,1c009694 <pos_libc_prf+0xf0a>
1c008a5a:	0076c0fb          	lp.setup	x1,a3,1c008a68 <pos_libc_prf+0x2de>
1c008a5e:	1c000737          	lui	a4,0x1c000
1c008a62:	05070713          	addi	a4,a4,80 # 1c000050 <__DTOR_END__+0x34>
1c008a66:	4318                	lw	a4,0(a4)
1c008a68:	00e7a22b          	p.sw	a4,4(a5!)
1c008a6c:	c205b7b3          	p.bclr	a5,a1,1,0
1c008a70:	00c784b3          	add	s1,a5,a2
1c008a74:	04b78c63          	beq	a5,a1,1c008acc <pos_libc_prf+0x342>
1c008a78:	198c                	addi	a1,sp,240
1c008a7a:	009586b3          	add	a3,a1,s1
1c008a7e:	02000793          	li	a5,32
1c008a82:	f2f68a23          	sb	a5,-204(a3)
1c008a86:	00148693          	addi	a3,s1,1
1c008a8a:	0526d163          	ble	s2,a3,1c008acc <pos_libc_prf+0x342>
1c008a8e:	96ae                	add	a3,a3,a1
1c008a90:	f2f68a23          	sb	a5,-204(a3)
1c008a94:	00248693          	addi	a3,s1,2
1c008a98:	0326da63          	ble	s2,a3,1c008acc <pos_libc_prf+0x342>
1c008a9c:	96ae                	add	a3,a3,a1
1c008a9e:	f2f68a23          	sb	a5,-204(a3)
1c008aa2:	00348693          	addi	a3,s1,3
1c008aa6:	0326d363          	ble	s2,a3,1c008acc <pos_libc_prf+0x342>
1c008aaa:	96ae                	add	a3,a3,a1
1c008aac:	f2f68a23          	sb	a5,-204(a3)
1c008ab0:	00448693          	addi	a3,s1,4
1c008ab4:	0126dc63          	ble	s2,a3,1c008acc <pos_libc_prf+0x342>
1c008ab8:	96ae                	add	a3,a3,a1
1c008aba:	f2f68a23          	sb	a5,-204(a3)
1c008abe:	00548713          	addi	a4,s1,5
1c008ac2:	01275563          	ble	s2,a4,1c008acc <pos_libc_prf+0x342>
1c008ac6:	972e                	add	a4,a4,a1
1c008ac8:	f2f70a23          	sb	a5,-204(a4)
1c008acc:	84ca                	mv	s1,s2
1c008ace:	d00482e3          	beqz	s1,1c0087d2 <pos_libc_prf+0x48>
1c008ad2:	8966                	mv	s2,s9
1c008ad4:	419d8db3          	sub	s11,s11,s9
1c008ad8:	a029                	j	1c008ae2 <pos_libc_prf+0x358>
1c008ada:	012d8733          	add	a4,s11,s2
1c008ade:	5a048f63          	beqz	s1,1c00909c <pos_libc_prf+0x912>
1c008ae2:	0019450b          	p.lbu	a0,1(s2!)
1c008ae6:	85ea                	mv	a1,s10
1c008ae8:	14fd                	addi	s1,s1,-1
1c008aea:	9b02                	jalr	s6
1c008aec:	fff537e3          	p.bneimm	a0,-1,1c008ada <pos_libc_prf+0x350>
1c008af0:	547d                	li	s0,-1
1c008af2:	b311                	j	1c0087f6 <pos_libc_prf+0x6c>
1c008af4:	4705                	li	a4,1
1c008af6:	ca3a                	sw	a4,20(sp)
1c008af8:	8456                	mv	s0,s5
1c008afa:	bbb5                	j	1c008876 <pos_libc_prf+0xec>
1c008afc:	03000713          	li	a4,48
1c008b00:	c83a                	sw	a4,16(sp)
1c008b02:	8456                	mv	s0,s5
1c008b04:	bb8d                	j	1c008876 <pos_libc_prf+0xec>
1c008b06:	4785                	li	a5,1
1c008b08:	ce3e                	sw	a5,28(sp)
1c008b0a:	8456                	mv	s0,s5
1c008b0c:	b3ad                	j	1c008876 <pos_libc_prf+0xec>
1c008b0e:	4685                	li	a3,1
1c008b10:	c636                	sw	a3,12(sp)
1c008b12:	8456                	mv	s0,s5
1c008b14:	b38d                	j	1c008876 <pos_libc_prf+0xec>
1c008b16:	8456                	mv	s0,s5
1c008b18:	0a85                	addi	s5,s5,1
1c008b1a:	00291793          	slli	a5,s2,0x2
1c008b1e:	97ca                	add	a5,a5,s2
1c008b20:	0786                	slli	a5,a5,0x1
1c008b22:	97a6                	add	a5,a5,s1
1c008b24:	000ac483          	lbu	s1,0(s5)
1c008b28:	fd078913          	addi	s2,a5,-48
1c008b2c:	fd048793          	addi	a5,s1,-48
1c008b30:	fef5f3e3          	bleu	a5,a1,1c008b16 <pos_libc_prf+0x38c>
1c008b34:	00240993          	addi	s3,s0,2
1c008b38:	a811                	j	1c008b4c <pos_libc_prf+0x3c2>
1c008b3a:	000c2903          	lw	s2,0(s8)
1c008b3e:	0c11                	addi	s8,s8,4
1c008b40:	12094d63          	bltz	s2,1c008c7a <pos_libc_prf+0x4f0>
1c008b44:	000ac483          	lbu	s1,0(s5)
1c008b48:	00240993          	addi	s3,s0,2
1c008b4c:	0c800693          	li	a3,200
1c008b50:	04d95933          	p.minu	s2,s2,a3
1c008b54:	b3a9                	j	1c00889e <pos_libc_prf+0x114>
1c008b56:	06500693          	li	a3,101
1c008b5a:	12d4d563          	ble	a3,s1,1c008c84 <pos_libc_prf+0x4fa>
1c008b5e:	04700693          	li	a3,71
1c008b62:	dc96cbe3          	blt	a3,s1,1c008938 <pos_libc_prf+0x1ae>
1c008b66:	04500693          	li	a3,69
1c008b6a:	10d4dd63          	ble	a3,s1,1c008c84 <pos_libc_prf+0x4fa>
1c008b6e:	c80483e3          	beqz	s1,1c0087f4 <pos_libc_prf+0x6a>
1c008b72:	02500693          	li	a3,37
1c008b76:	70d49863          	bne	s1,a3,1c009286 <pos_libc_prf+0xafc>
1c008b7a:	85ea                	mv	a1,s10
1c008b7c:	02500513          	li	a0,37
1c008b80:	9b02                	jalr	s6
1c008b82:	f7f527e3          	p.beqimm	a0,-1,1c008af0 <pos_libc_prf+0x366>
1c008b86:	0d85                	addi	s11,s11,1
1c008b88:	b195                	j	1c0087ec <pos_libc_prf+0x62>
1c008b8a:	0009c783          	lbu	a5,0(s3)
1c008b8e:	02a00693          	li	a3,42
1c008b92:	00198513          	addi	a0,s3,1
1c008b96:	0ad79963          	bne	a5,a3,1c008c48 <pos_libc_prf+0x4be>
1c008b9a:	000c2a03          	lw	s4,0(s8)
1c008b9e:	0019c483          	lbu	s1,1(s3)
1c008ba2:	0c11                	addi	s8,s8,4
1c008ba4:	0989                	addi	s3,s3,2
1c008ba6:	0c800693          	li	a3,200
1c008baa:	cf46dfe3          	ble	s4,a3,1c0088a8 <pos_libc_prf+0x11e>
1c008bae:	5a7d                	li	s4,-1
1c008bb0:	b9e5                	j	1c0088a8 <pos_libc_prf+0x11e>
1c008bb2:	06e00693          	li	a3,110
1c008bb6:	58d48763          	beq	s1,a3,1c009144 <pos_libc_prf+0x9ba>
1c008bba:	5896dc63          	ble	s1,a3,1c009152 <pos_libc_prf+0x9c8>
1c008bbe:	47b2                	lw	a5,12(sp)
1c008bc0:	004c0813          	addi	a6,s8,4
1c008bc4:	000c2603          	lw	a2,0(s8)
1c008bc8:	04078ee3          	beqz	a5,1c009424 <pos_libc_prf+0xc9a>
1c008bcc:	03000793          	li	a5,48
1c008bd0:	02f10223          	sb	a5,36(sp)
1c008bd4:	02060de3          	beqz	a2,1c00940e <pos_libc_prf+0xc84>
1c008bd8:	02510513          	addi	a0,sp,37
1c008bdc:	86aa                	mv	a3,a0
1c008bde:	87b6                	mv	a5,a3
1c008be0:	f8363733          	p.bclr	a4,a2,28,3
1c008be4:	03070713          	addi	a4,a4,48
1c008be8:	820d                	srli	a2,a2,0x3
1c008bea:	00e780ab          	p.sb	a4,1(a5!)
1c008bee:	fa6d                	bnez	a2,1c008be0 <pos_libc_prf+0x456>
1c008bf0:	40a78733          	sub	a4,a5,a0
1c008bf4:	01475d63          	ble	s4,a4,1c008c0e <pos_libc_prf+0x484>
1c008bf8:	40fa0633          	sub	a2,s4,a5
1c008bfc:	03000593          	li	a1,48
1c008c00:	962a                	add	a2,a2,a0
1c008c02:	004640fb          	lp.setup	x1,a2,1c008c0a <pos_libc_prf+0x480>
1c008c06:	00b780ab          	p.sb	a1,1(a5!)
1c008c0a:	40a78733          	sub	a4,a5,a0
1c008c0e:	fe078fab          	p.sb	zero,-1(a5!)
1c008c12:	00f6fc63          	bleu	a5,a3,1c008c2a <pos_libc_prf+0x4a0>
1c008c16:	0006c583          	lbu	a1,0(a3)
1c008c1a:	0007c603          	lbu	a2,0(a5)
1c008c1e:	feb78fab          	p.sb	a1,-1(a5!)
1c008c22:	00c680ab          	p.sb	a2,1(a3!)
1c008c26:	fef6e8e3          	bltu	a3,a5,1c008c16 <pos_libc_prf+0x48c>
1c008c2a:	46b2                	lw	a3,12(sp)
1c008c2c:	0c800793          	li	a5,200
1c008c30:	00d704b3          	add	s1,a4,a3
1c008c34:	0bfa2de3          	p.beqimm	s4,-1,1c0094ee <pos_libc_prf+0xd64>
1c008c38:	ea97cce3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c008c3c:	02000793          	li	a5,32
1c008c40:	8c42                	mv	s8,a6
1c008c42:	c602                	sw	zero,12(sp)
1c008c44:	c83e                	sw	a5,16(sp)
1c008c46:	b35d                	j	1c0089ec <pos_libc_prf+0x262>
1c008c48:	fd078813          	addi	a6,a5,-48
1c008c4c:	46a5                	li	a3,9
1c008c4e:	84be                	mv	s1,a5
1c008c50:	862a                	mv	a2,a0
1c008c52:	4a01                	li	s4,0
1c008c54:	45a5                	li	a1,9
1c008c56:	89aa                	mv	s3,a0
1c008c58:	c506e8e3          	bltu	a3,a6,1c0088a8 <pos_libc_prf+0x11e>
1c008c5c:	002a1793          	slli	a5,s4,0x2
1c008c60:	97d2                	add	a5,a5,s4
1c008c62:	0786                	slli	a5,a5,0x1
1c008c64:	97a6                	add	a5,a5,s1
1c008c66:	0016448b          	p.lbu	s1,1(a2!)
1c008c6a:	fd078a13          	addi	s4,a5,-48
1c008c6e:	fd048793          	addi	a5,s1,-48
1c008c72:	fef5f5e3          	bleu	a5,a1,1c008c5c <pos_libc_prf+0x4d2>
1c008c76:	89b2                	mv	s3,a2
1c008c78:	b73d                	j	1c008ba6 <pos_libc_prf+0x41c>
1c008c7a:	4705                	li	a4,1
1c008c7c:	41200933          	neg	s2,s2
1c008c80:	ce3a                	sw	a4,28(sp)
1c008c82:	b5c9                	j	1c008b44 <pos_libc_prf+0x3ba>
1c008c84:	0c1d                	addi	s8,s8,7
1c008c86:	c40c3c33          	p.bclr	s8,s8,2,0
1c008c8a:	000c2683          	lw	a3,0(s8)
1c008c8e:	004c2803          	lw	a6,4(s8)
1c008c92:	7ff00613          	li	a2,2047
1c008c96:	0156d893          	srli	a7,a3,0x15
1c008c9a:	01485513          	srli	a0,a6,0x14
1c008c9e:	00b81593          	slli	a1,a6,0xb
1c008ca2:	00b8e5b3          	or	a1,a7,a1
1c008ca6:	e8b53533          	p.bclr	a0,a0,20,11
1c008caa:	0c21                	addi	s8,s8,8
1c008cac:	06ae                	slli	a3,a3,0xb
1c008cae:	c1f5b5b3          	p.bclr	a1,a1,0,31
1c008cb2:	7ac50b63          	beq	a0,a2,1c009468 <pos_libc_prf+0xcde>
1c008cb6:	04600613          	li	a2,70
1c008cba:	00c49463          	bne	s1,a2,1c008cc2 <pos_libc_prf+0x538>
1c008cbe:	06600493          	li	s1,102
1c008cc2:	00d56633          	or	a2,a0,a3
1c008cc6:	8e4d                	or	a2,a2,a1
1c008cc8:	7c060b63          	beqz	a2,1c00949e <pos_libc_prf+0xd14>
1c008ccc:	c0250513          	addi	a0,a0,-1022
1c008cd0:	c1f5c333          	p.bset	t1,a1,0,31
1c008cd4:	140842e3          	bltz	a6,1c009618 <pos_libc_prf+0xe8e>
1c008cd8:	4752                	lw	a4,20(sp)
1c008cda:	180703e3          	beqz	a4,1c009660 <pos_libc_prf+0xed6>
1c008cde:	02b00613          	li	a2,43
1c008ce2:	02c10223          	sb	a2,36(sp)
1c008ce6:	02510893          	addi	a7,sp,37
1c008cea:	5679                	li	a2,-2
1c008cec:	4801                	li	a6,0
1c008cee:	06c55763          	ble	a2,a0,1c008d5c <pos_libc_prf+0x5d2>
1c008cf2:	33333e37          	lui	t3,0x33333
1c008cf6:	80000eb7          	lui	t4,0x80000
1c008cfa:	332e0e13          	addi	t3,t3,818 # 33333332 <__cluster_text_end+0x17323332>
1c008cfe:	fffece93          	not	t4,t4
1c008d02:	5f79                	li	t5,-2
1c008d04:	a011                	j	1c008d08 <pos_libc_prf+0x57e>
1c008d06:	853e                	mv	a0,a5
1c008d08:	01f31613          	slli	a2,t1,0x1f
1c008d0c:	0016d713          	srli	a4,a3,0x1
1c008d10:	fc16b7b3          	p.bclr	a5,a3,30,1
1c008d14:	8f51                	or	a4,a4,a2
1c008d16:	00e786b3          	add	a3,a5,a4
1c008d1a:	00f6b7b3          	sltu	a5,a3,a5
1c008d1e:	00135313          	srli	t1,t1,0x1
1c008d22:	933e                	add	t1,t1,a5
1c008d24:	00150793          	addi	a5,a0,1
1c008d28:	fc6e6fe3          	bltu	t3,t1,1c008d06 <pos_libc_prf+0x57c>
1c008d2c:	00269613          	slli	a2,a3,0x2
1c008d30:	01e6d593          	srli	a1,a3,0x1e
1c008d34:	00231713          	slli	a4,t1,0x2
1c008d38:	96b2                	add	a3,a3,a2
1c008d3a:	8f4d                	or	a4,a4,a1
1c008d3c:	933a                	add	t1,t1,a4
1c008d3e:	00c6b633          	sltu	a2,a3,a2
1c008d42:	9332                	add	t1,t1,a2
1c008d44:	01f6d713          	srli	a4,a3,0x1f
1c008d48:	0509                	addi	a0,a0,2
1c008d4a:	187d                	addi	a6,a6,-1
1c008d4c:	01d31663          	bne	t1,t4,1c008d58 <pos_libc_prf+0x5ce>
1c008d50:	0686                	slli	a3,a3,0x1
1c008d52:	fc174333          	p.bset	t1,a4,30,1
1c008d56:	853e                	mv	a0,a5
1c008d58:	fbe548e3          	blt	a0,t5,1c008d08 <pos_libc_prf+0x57e>
1c008d5c:	06a05763          	blez	a0,1c008dca <pos_libc_prf+0x640>
1c008d60:	80000eb7          	lui	t4,0x80000
1c008d64:	4f15                	li	t5,5
1c008d66:	fffece93          	not	t4,t4
1c008d6a:	00268613          	addi	a2,a3,2
1c008d6e:	00d636b3          	sltu	a3,a2,a3
1c008d72:	9336                	add	t1,t1,a3
1c008d74:	03e357b3          	divu	a5,t1,t5
1c008d78:	00365593          	srli	a1,a2,0x3
1c008d7c:	157d                	addi	a0,a0,-1
1c008d7e:	0805                	addi	a6,a6,1
1c008d80:	00279713          	slli	a4,a5,0x2
1c008d84:	973e                	add	a4,a4,a5
1c008d86:	40e30333          	sub	t1,t1,a4
1c008d8a:	01d31713          	slli	a4,t1,0x1d
1c008d8e:	8dd9                	or	a1,a1,a4
1c008d90:	03e5d5b3          	divu	a1,a1,t5
1c008d94:	00359693          	slli	a3,a1,0x3
1c008d98:	00559713          	slli	a4,a1,0x5
1c008d9c:	9736                	add	a4,a4,a3
1c008d9e:	40e60733          	sub	a4,a2,a4
1c008da2:	03e75733          	divu	a4,a4,t5
1c008da6:	81f5                	srli	a1,a1,0x1d
1c008da8:	97ae                	add	a5,a5,a1
1c008daa:	96ba                	add	a3,a3,a4
1c008dac:	00e6b733          	sltu	a4,a3,a4
1c008db0:	00f70333          	add	t1,a4,a5
1c008db4:	01f6d793          	srli	a5,a3,0x1f
1c008db8:	0306                	slli	t1,t1,0x1
1c008dba:	0067e333          	or	t1,a5,t1
1c008dbe:	0686                	slli	a3,a3,0x1
1c008dc0:	157d                	addi	a0,a0,-1
1c008dc2:	fe6ef9e3          	bleu	t1,t4,1c008db4 <pos_libc_prf+0x62a>
1c008dc6:	faa042e3          	bgtz	a0,1c008d6a <pos_libc_prf+0x5e0>
1c008dca:	4611                	li	a2,4
1c008dcc:	8e09                	sub	a2,a2,a0
1c008dce:	012640fb          	lp.setup	x1,a2,1c008df2 <pos_libc_prf+0x668>
1c008dd2:	01f31713          	slli	a4,t1,0x1f
1c008dd6:	0016d793          	srli	a5,a3,0x1
1c008dda:	8fd9                	or	a5,a5,a4
1c008ddc:	fc16b6b3          	p.bclr	a3,a3,30,1
1c008de0:	00f68eb3          	add	t4,a3,a5
1c008de4:	00135313          	srli	t1,t1,0x1
1c008de8:	00deb6b3          	sltu	a3,t4,a3
1c008dec:	00668533          	add	a0,a3,t1
1c008df0:	832a                	mv	t1,a0
1c008df2:	86f6                	mv	a3,t4
1c008df4:	06700693          	li	a3,103
1c008df8:	6c0a4e63          	bltz	s4,1c0094d4 <pos_libc_prf+0xd4a>
1c008dfc:	62d48863          	beq	s1,a3,1c00942c <pos_libc_prf+0xca2>
1c008e00:	04700693          	li	a3,71
1c008e04:	62d48463          	beq	s1,a3,1c00942c <pos_libc_prf+0xca2>
1c008e08:	06600693          	li	a3,102
1c008e0c:	78d48963          	beq	s1,a3,1c00959e <pos_libc_prf+0xe14>
1c008e10:	001a0f13          	addi	t5,s4,1
1c008e14:	45c1                	li	a1,16
1c008e16:	04bf4f33          	p.min	t5,t5,a1
1c008e1a:	1f7d                	addi	t5,t5,-1
1c008e1c:	4e01                	li	t3,0
1c008e1e:	4581                	li	a1,0
1c008e20:	080006b7          	lui	a3,0x8000
1c008e24:	4f95                	li	t6,5
1c008e26:	0f05                	addi	t5,t5,1
1c008e28:	02ff40fb          	lp.setup	x1,t5,1c008e86 <pos_libc_prf+0x6fc>
1c008e2c:	00258713          	addi	a4,a1,2
1c008e30:	00b737b3          	sltu	a5,a4,a1
1c008e34:	97b6                	add	a5,a5,a3
1c008e36:	03f7d5b3          	divu	a1,a5,t6
1c008e3a:	00375613          	srli	a2,a4,0x3
1c008e3e:	00259693          	slli	a3,a1,0x2
1c008e42:	96ae                	add	a3,a3,a1
1c008e44:	8f95                	sub	a5,a5,a3
1c008e46:	07f6                	slli	a5,a5,0x1d
1c008e48:	8e5d                	or	a2,a2,a5
1c008e4a:	03f65633          	divu	a2,a2,t6
1c008e4e:	00361693          	slli	a3,a2,0x3
1c008e52:	00561793          	slli	a5,a2,0x5
1c008e56:	97b6                	add	a5,a5,a3
1c008e58:	40f707b3          	sub	a5,a4,a5
1c008e5c:	03f7d7b3          	divu	a5,a5,t6
1c008e60:	01d65713          	srli	a4,a2,0x1d
1c008e64:	972e                	add	a4,a4,a1
1c008e66:	96be                	add	a3,a3,a5
1c008e68:	00f6b7b3          	sltu	a5,a3,a5
1c008e6c:	973e                	add	a4,a4,a5
1c008e6e:	01f71613          	slli	a2,a4,0x1f
1c008e72:	0016d793          	srli	a5,a3,0x1
1c008e76:	8fd1                	or	a5,a5,a2
1c008e78:	fc16b6b3          	p.bclr	a3,a3,30,1
1c008e7c:	00f685b3          	add	a1,a3,a5
1c008e80:	8305                	srli	a4,a4,0x1
1c008e82:	00d5b6b3          	sltu	a3,a1,a3
1c008e86:	96ba                	add	a3,a3,a4
1c008e88:	95f6                	add	a1,a1,t4
1c008e8a:	96aa                	add	a3,a3,a0
1c008e8c:	01d5beb3          	sltu	t4,a1,t4
1c008e90:	00de8533          	add	a0,t4,a3
1c008e94:	f6053633          	p.bclr	a2,a0,27,0
1c008e98:	86ae                	mv	a3,a1
1c008e9a:	c22d                	beqz	a2,1c008efc <pos_libc_prf+0x772>
1c008e9c:	00258613          	addi	a2,a1,2
1c008ea0:	00b636b3          	sltu	a3,a2,a1
1c008ea4:	96aa                	add	a3,a3,a0
1c008ea6:	4e95                	li	t4,5
1c008ea8:	03d6d333          	divu	t1,a3,t4
1c008eac:	00365513          	srli	a0,a2,0x3
1c008eb0:	0805                	addi	a6,a6,1
1c008eb2:	00231593          	slli	a1,t1,0x2
1c008eb6:	959a                	add	a1,a1,t1
1c008eb8:	8e8d                	sub	a3,a3,a1
1c008eba:	06f6                	slli	a3,a3,0x1d
1c008ebc:	8d55                	or	a0,a0,a3
1c008ebe:	03d55533          	divu	a0,a0,t4
1c008ec2:	00351593          	slli	a1,a0,0x3
1c008ec6:	00551693          	slli	a3,a0,0x5
1c008eca:	96ae                	add	a3,a3,a1
1c008ecc:	40d606b3          	sub	a3,a2,a3
1c008ed0:	03d6d6b3          	divu	a3,a3,t4
1c008ed4:	8175                	srli	a0,a0,0x1d
1c008ed6:	951a                	add	a0,a0,t1
1c008ed8:	95b6                	add	a1,a1,a3
1c008eda:	00d5b6b3          	sltu	a3,a1,a3
1c008ede:	00a68633          	add	a2,a3,a0
1c008ee2:	01f61513          	slli	a0,a2,0x1f
1c008ee6:	0015d693          	srli	a3,a1,0x1
1c008eea:	8ec9                	or	a3,a3,a0
1c008eec:	fc15b5b3          	p.bclr	a1,a1,30,1
1c008ef0:	96ae                	add	a3,a3,a1
1c008ef2:	8205                	srli	a2,a2,0x1
1c008ef4:	00b6b5b3          	sltu	a1,a3,a1
1c008ef8:	00c58533          	add	a0,a1,a2
1c008efc:	06600593          	li	a1,102
1c008f00:	00188613          	addi	a2,a7,1
1c008f04:	60b48463          	beq	s1,a1,1c00950c <pos_libc_prf+0xd82>
1c008f08:	00269593          	slli	a1,a3,0x2
1c008f0c:	01e6de93          	srli	t4,a3,0x1e
1c008f10:	00251313          	slli	t1,a0,0x2
1c008f14:	96ae                	add	a3,a3,a1
1c008f16:	006ee333          	or	t1,t4,t1
1c008f1a:	00b6b5b3          	sltu	a1,a3,a1
1c008f1e:	951a                	add	a0,a0,t1
1c008f20:	952e                	add	a0,a0,a1
1c008f22:	0506                	slli	a0,a0,0x1
1c008f24:	01f6d593          	srli	a1,a3,0x1f
1c008f28:	8d4d                	or	a0,a0,a1
1c008f2a:	01c55593          	srli	a1,a0,0x1c
1c008f2e:	03058313          	addi	t1,a1,48
1c008f32:	47b2                	lw	a5,12(sp)
1c008f34:	10000737          	lui	a4,0x10000
1c008f38:	00b035b3          	snez	a1,a1
1c008f3c:	177d                	addi	a4,a4,-1
1c008f3e:	00688023          	sb	t1,0(a7)
1c008f42:	0686                	slli	a3,a3,0x1
1c008f44:	8d79                	and	a0,a0,a4
1c008f46:	40b80833          	sub	a6,a6,a1
1c008f4a:	5a078863          	beqz	a5,1c0094fa <pos_libc_prf+0xd70>
1c008f4e:	02e00613          	li	a2,46
1c008f52:	00c880a3          	sb	a2,1(a7)
1c008f56:	00288613          	addi	a2,a7,2
1c008f5a:	040a0b63          	beqz	s4,1c008fb0 <pos_libc_prf+0x826>
1c008f5e:	8332                	mv	t1,a2
1c008f60:	9a32                	add	s4,s4,a2
1c008f62:	4ebd                	li	t4,15
1c008f64:	03000f13          	li	t5,48
1c008f68:	00269793          	slli	a5,a3,0x2
1c008f6c:	01e6d593          	srli	a1,a3,0x1e
1c008f70:	00251713          	slli	a4,a0,0x2
1c008f74:	00d78633          	add	a2,a5,a3
1c008f78:	8f4d                	or	a4,a4,a1
1c008f7a:	972a                	add	a4,a4,a0
1c008f7c:	00f637b3          	sltu	a5,a2,a5
1c008f80:	97ba                	add	a5,a5,a4
1c008f82:	0786                	slli	a5,a5,0x1
1c008f84:	01f65713          	srli	a4,a2,0x1f
1c008f88:	8fd9                	or	a5,a5,a4
1c008f8a:	01c7d713          	srli	a4,a5,0x1c
1c008f8e:	03070713          	addi	a4,a4,48 # 10000030 <__l2_shared_end+0x28>
1c008f92:	2fd05463          	blez	t4,1c00927a <pos_libc_prf+0xaf0>
1c008f96:	100005b7          	lui	a1,0x10000
1c008f9a:	15fd                	addi	a1,a1,-1
1c008f9c:	00e300ab          	p.sb	a4,1(t1!)
1c008fa0:	1efd                	addi	t4,t4,-1
1c008fa2:	00161693          	slli	a3,a2,0x1
1c008fa6:	00b7f533          	and	a0,a5,a1
1c008faa:	fa6a1fe3          	bne	s4,t1,1c008f68 <pos_libc_prf+0x7de>
1c008fae:	8652                	mv	a2,s4
1c008fb0:	0c0e1163          	bnez	t3,1c009072 <pos_libc_prf+0x8e8>
1c008fb4:	c054b6b3          	p.bclr	a3,s1,0,5
1c008fb8:	04500593          	li	a1,69
1c008fbc:	02b69963          	bne	a3,a1,1c008fee <pos_libc_prf+0x864>
1c008fc0:	87a6                	mv	a5,s1
1c008fc2:	00f60023          	sb	a5,0(a2)
1c008fc6:	5e084d63          	bltz	a6,1c0095c0 <pos_libc_prf+0xe36>
1c008fca:	02b00793          	li	a5,43
1c008fce:	00f600a3          	sb	a5,1(a2)
1c008fd2:	47a9                	li	a5,10
1c008fd4:	02f846b3          	div	a3,a6,a5
1c008fd8:	0611                	addi	a2,a2,4
1c008fda:	02f867b3          	rem	a5,a6,a5
1c008fde:	03068693          	addi	a3,a3,48 # 8000030 <__l1_heap_size+0x7ff0038>
1c008fe2:	fed60f23          	sb	a3,-2(a2)
1c008fe6:	03078793          	addi	a5,a5,48
1c008fea:	fef60fa3          	sb	a5,-1(a2)
1c008fee:	00060023          	sb	zero,0(a2)
1c008ff2:	419604b3          	sub	s1,a2,s9
1c008ff6:	46d2                	lw	a3,20(sp)
1c008ff8:	4762                	lw	a4,24(sp)
1c008ffa:	8ed9                	or	a3,a3,a4
1c008ffc:	c636                	sw	a3,12(sp)
1c008ffe:	2a069463          	bnez	a3,1c0092a6 <pos_libc_prf+0xb1c>
1c009002:	02414683          	lbu	a3,36(sp)
1c009006:	02d00793          	li	a5,45
1c00900a:	28f68e63          	beq	a3,a5,1c0092a6 <pos_libc_prf+0xb1c>
1c00900e:	0c800793          	li	a5,200
1c009012:	9c97dde3          	ble	s1,a5,1c0089ec <pos_libc_prf+0x262>
1c009016:	547d                	li	s0,-1
1c009018:	fdeff06f          	j	1c0087f6 <pos_libc_prf+0x6c>
1c00901c:	0305                	addi	t1,t1,1
1c00901e:	00269793          	slli	a5,a3,0x2
1c009022:	01e6d893          	srli	a7,a3,0x1e
1c009026:	00251713          	slli	a4,a0,0x2
1c00902a:	00d785b3          	add	a1,a5,a3
1c00902e:	00e8e733          	or	a4,a7,a4
1c009032:	972a                	add	a4,a4,a0
1c009034:	00f5b7b3          	sltu	a5,a1,a5
1c009038:	97ba                	add	a5,a5,a4
1c00903a:	0786                	slli	a5,a5,0x1
1c00903c:	01f5d713          	srli	a4,a1,0x1f
1c009040:	8fd9                	or	a5,a5,a4
1c009042:	01c7d893          	srli	a7,a5,0x1c
1c009046:	03000713          	li	a4,48
1c00904a:	01d05c63          	blez	t4,1c009062 <pos_libc_prf+0x8d8>
1c00904e:	00159693          	slli	a3,a1,0x1
1c009052:	100005b7          	lui	a1,0x10000
1c009056:	15fd                	addi	a1,a1,-1
1c009058:	03088713          	addi	a4,a7,48
1c00905c:	1efd                	addi	t4,t4,-1
1c00905e:	00b7f533          	and	a0,a5,a1
1c009062:	fee30fa3          	sb	a4,-1(t1)
1c009066:	fa661be3          	bne	a2,t1,1c00901c <pos_libc_prf+0x892>
1c00906a:	014f8633          	add	a2,t6,s4
1c00906e:	f80e00e3          	beqz	t3,1c008fee <pos_libc_prf+0x864>
1c009072:	03000513          	li	a0,48
1c009076:	a011                	j	1c00907a <pos_libc_prf+0x8f0>
1c009078:	8636                	mv	a2,a3
1c00907a:	fff60693          	addi	a3,a2,-1
1c00907e:	0006c583          	lbu	a1,0(a3)
1c009082:	fea58be3          	beq	a1,a0,1c009078 <pos_libc_prf+0x8ee>
1c009086:	02e00513          	li	a0,46
1c00908a:	f2a595e3          	bne	a1,a0,1c008fb4 <pos_libc_prf+0x82a>
1c00908e:	8636                	mv	a2,a3
1c009090:	b715                	j	1c008fb4 <pos_libc_prf+0x82a>
1c009092:	00f680ab          	p.sb	a5,1(a3!)
1c009096:	8c051ce3          	bnez	a0,1c00896e <pos_libc_prf+0x1e4>
1c00909a:	b8c5                	j	1c00898a <pos_libc_prf+0x200>
1c00909c:	8dba                	mv	s11,a4
1c00909e:	f34ff06f          	j	1c0087d2 <pos_libc_prf+0x48>
1c0090a2:	77e1                	lui	a5,0xffff8
1c0090a4:	8307c793          	xori	a5,a5,-2000
1c0090a8:	02610693          	addi	a3,sp,38
1c0090ac:	000c2583          	lw	a1,0(s8)
1c0090b0:	02f11223          	sh	a5,36(sp)
1c0090b4:	0c11                	addi	s8,s8,4
1c0090b6:	87b6                	mv	a5,a3
1c0090b8:	48a5                	li	a7,9
1c0090ba:	f645b633          	p.bclr	a2,a1,27,4
1c0090be:	0ff67713          	andi	a4,a2,255
1c0090c2:	03070513          	addi	a0,a4,48
1c0090c6:	8191                	srli	a1,a1,0x4
1c0090c8:	05770713          	addi	a4,a4,87
1c0090cc:	06c8e863          	bltu	a7,a2,1c00913c <pos_libc_prf+0x9b2>
1c0090d0:	00a780ab          	p.sb	a0,1(a5!) # ffff8001 <pulp__FC+0xffff8002>
1c0090d4:	f1fd                	bnez	a1,1c0090ba <pos_libc_prf+0x930>
1c0090d6:	40d78733          	sub	a4,a5,a3
1c0090da:	461d                	li	a2,7
1c0090dc:	02e64563          	blt	a2,a4,1c009106 <pos_libc_prf+0x97c>
1c0090e0:	1998                	addi	a4,sp,240
1c0090e2:	40e78533          	sub	a0,a5,a4
1c0090e6:	40f68633          	sub	a2,a3,a5
1c0090ea:	0cb50513          	addi	a0,a0,203
1c0090ee:	4821                	li	a6,8
1c0090f0:	03000593          	li	a1,48
1c0090f4:	0621                	addi	a2,a2,8
1c0090f6:	5aa84263          	blt	a6,a0,1c00969a <pos_libc_prf+0xf10>
1c0090fa:	004640fb          	lp.setup	x1,a2,1c009102 <pos_libc_prf+0x978>
1c0090fe:	00b780ab          	p.sb	a1,1(a5!)
1c009102:	40d78733          	sub	a4,a5,a3
1c009106:	fe078fab          	p.sb	zero,-1(a5!)
1c00910a:	00f6fc63          	bleu	a5,a3,1c009122 <pos_libc_prf+0x998>
1c00910e:	0006c583          	lbu	a1,0(a3)
1c009112:	0007c603          	lbu	a2,0(a5)
1c009116:	feb78fab          	p.sb	a1,-1(a5!)
1c00911a:	00c680ab          	p.sb	a2,1(a3!)
1c00911e:	fef6e8e3          	bltu	a3,a5,1c00910e <pos_libc_prf+0x984>
1c009122:	00270493          	addi	s1,a4,2
1c009126:	0c800793          	li	a5,200
1c00912a:	17fa2963          	p.beqimm	s4,-1,1c00929c <pos_libc_prf+0xb12>
1c00912e:	9c97c1e3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c009132:	02000713          	li	a4,32
1c009136:	c602                	sw	zero,12(sp)
1c009138:	c83a                	sw	a4,16(sp)
1c00913a:	b84d                	j	1c0089ec <pos_libc_prf+0x262>
1c00913c:	00e780ab          	p.sb	a4,1(a5!)
1c009140:	fdad                	bnez	a1,1c0090ba <pos_libc_prf+0x930>
1c009142:	bf51                	j	1c0090d6 <pos_libc_prf+0x94c>
1c009144:	000c2783          	lw	a5,0(s8)
1c009148:	0c11                	addi	s8,s8,4
1c00914a:	01b7a023          	sw	s11,0(a5)
1c00914e:	e84ff06f          	j	1c0087d2 <pos_libc_prf+0x48>
1c009152:	06900693          	li	a3,105
1c009156:	12d49863          	bne	s1,a3,1c009286 <pos_libc_prf+0xafc>
1c00915a:	000c2503          	lw	a0,0(s8)
1c00915e:	0c11                	addi	s8,s8,4
1c009160:	34054d63          	bltz	a0,1c0094ba <pos_libc_prf+0xd30>
1c009164:	4652                	lw	a2,20(sp)
1c009166:	86aa                	mv	a3,a0
1c009168:	2e061963          	bnez	a2,1c00945a <pos_libc_prf+0xcd0>
1c00916c:	4762                	lw	a4,24(sp)
1c00916e:	87e6                	mv	a5,s9
1c009170:	c719                	beqz	a4,1c00917e <pos_libc_prf+0x9f4>
1c009172:	02000793          	li	a5,32
1c009176:	02f10223          	sb	a5,36(sp)
1c00917a:	02510793          	addi	a5,sp,37
1c00917e:	873e                	mv	a4,a5
1c009180:	45a9                	li	a1,10
1c009182:	02b6f633          	remu	a2,a3,a1
1c009186:	02b6d6b3          	divu	a3,a3,a1
1c00918a:	03060613          	addi	a2,a2,48
1c00918e:	00c700ab          	p.sb	a2,1(a4!)
1c009192:	fae5                	bnez	a3,1c009182 <pos_libc_prf+0x9f8>
1c009194:	40f706b3          	sub	a3,a4,a5
1c009198:	0146dc63          	ble	s4,a3,1c0091b0 <pos_libc_prf+0xa26>
1c00919c:	40e786b3          	sub	a3,a5,a4
1c0091a0:	03000613          	li	a2,48
1c0091a4:	96d2                	add	a3,a3,s4
1c0091a6:	0046c0fb          	lp.setup	x1,a3,1c0091ae <pos_libc_prf+0xa24>
1c0091aa:	00c700ab          	p.sb	a2,1(a4!)
1c0091ae:	0001                	nop
1c0091b0:	86ba                	mv	a3,a4
1c0091b2:	fe068fab          	p.sb	zero,-1(a3!)
1c0091b6:	00d7fc63          	bleu	a3,a5,1c0091ce <pos_libc_prf+0xa44>
1c0091ba:	0007c583          	lbu	a1,0(a5)
1c0091be:	0006c603          	lbu	a2,0(a3)
1c0091c2:	feb68fab          	p.sb	a1,-1(a3!)
1c0091c6:	00c780ab          	p.sb	a2,1(a5!)
1c0091ca:	fed7e8e3          	bltu	a5,a3,1c0091ba <pos_libc_prf+0xa30>
1c0091ce:	47d2                	lw	a5,20(sp)
1c0091d0:	4662                	lw	a2,24(sp)
1c0091d2:	419704b3          	sub	s1,a4,s9
1c0091d6:	8fd1                	or	a5,a5,a2
1c0091d8:	c63e                	sw	a5,12(sp)
1c0091da:	e399                	bnez	a5,1c0091e0 <pos_libc_prf+0xa56>
1c0091dc:	817d                	srli	a0,a0,0x1f
1c0091de:	c62a                	sw	a0,12(sp)
1c0091e0:	e3fa27e3          	p.beqimm	s4,-1,1c00900e <pos_libc_prf+0x884>
1c0091e4:	0c800793          	li	a5,200
1c0091e8:	9097c4e3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c0091ec:	02000713          	li	a4,32
1c0091f0:	c83a                	sw	a4,16(sp)
1c0091f2:	ffaff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c0091f6:	000c2783          	lw	a5,0(s8)
1c0091fa:	020102a3          	sb	zero,37(sp)
1c0091fe:	0c11                	addi	s8,s8,4
1c009200:	02f10223          	sb	a5,36(sp)
1c009204:	4485                	li	s1,1
1c009206:	f16ff06f          	j	1c00891c <pos_libc_prf+0x192>
1c00920a:	000c2683          	lw	a3,0(s8)
1c00920e:	87e6                	mv	a5,s9
1c009210:	0c11                	addi	s8,s8,4
1c009212:	45a9                	li	a1,10
1c009214:	02b6f733          	remu	a4,a3,a1
1c009218:	02b6d6b3          	divu	a3,a3,a1
1c00921c:	03070713          	addi	a4,a4,48
1c009220:	00e780ab          	p.sb	a4,1(a5!)
1c009224:	fae5                	bnez	a3,1c009214 <pos_libc_prf+0xa8a>
1c009226:	419784b3          	sub	s1,a5,s9
1c00922a:	0144dd63          	ble	s4,s1,1c009244 <pos_libc_prf+0xaba>
1c00922e:	40fc86b3          	sub	a3,s9,a5
1c009232:	03000613          	li	a2,48
1c009236:	96d2                	add	a3,a3,s4
1c009238:	0046c0fb          	lp.setup	x1,a3,1c009240 <pos_libc_prf+0xab6>
1c00923c:	00c780ab          	p.sb	a2,1(a5!)
1c009240:	419784b3          	sub	s1,a5,s9
1c009244:	fe078fab          	p.sb	zero,-1(a5!)
1c009248:	00fcfd63          	bleu	a5,s9,1c009262 <pos_libc_prf+0xad8>
1c00924c:	86e6                	mv	a3,s9
1c00924e:	0006c603          	lbu	a2,0(a3)
1c009252:	0007c703          	lbu	a4,0(a5)
1c009256:	fec78fab          	p.sb	a2,-1(a5!)
1c00925a:	00e680ab          	p.sb	a4,1(a3!)
1c00925e:	fef6e8e3          	bltu	a3,a5,1c00924e <pos_libc_prf+0xac4>
1c009262:	0c800793          	li	a5,200
1c009266:	03fa2b63          	p.beqimm	s4,-1,1c00929c <pos_libc_prf+0xb12>
1c00926a:	8897c3e3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c00926e:	02000693          	li	a3,32
1c009272:	c602                	sw	zero,12(sp)
1c009274:	c836                	sw	a3,16(sp)
1c009276:	f76ff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c00927a:	01e300ab          	p.sb	t5,1(t1!)
1c00927e:	ce6a15e3          	bne	s4,t1,1c008f68 <pos_libc_prf+0x7de>
1c009282:	8652                	mv	a2,s4
1c009284:	b335                	j	1c008fb0 <pos_libc_prf+0x826>
1c009286:	0c800693          	li	a3,200
1c00928a:	d496d463          	ble	s1,a3,1c0087d2 <pos_libc_prf+0x48>
1c00928e:	547d                	li	s0,-1
1c009290:	d66ff06f          	j	1c0087f6 <pos_libc_prf+0x6c>
1c009294:	e60a5b63          	bgez	s4,1c00890a <pos_libc_prf+0x180>
1c009298:	e76ff06f          	j	1c00890e <pos_libc_prf+0x184>
1c00929c:	8497cae3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c0092a0:	c602                	sw	zero,12(sp)
1c0092a2:	f4aff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c0092a6:	0c800793          	li	a5,200
1c0092aa:	8497c3e3          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c0092ae:	4685                	li	a3,1
1c0092b0:	c636                	sw	a3,12(sp)
1c0092b2:	f3aff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c0092b6:	409909b3          	sub	s3,s2,s1
1c0092ba:	00148613          	addi	a2,s1,1
1c0092be:	85e6                	mv	a1,s9
1c0092c0:	013c8533          	add	a0,s9,s3
1c0092c4:	9eaff0ef          	jal	ra,1c0084ae <memmove>
1c0092c8:	46c2                	lw	a3,16(sp)
1c0092ca:	02000793          	li	a5,32
1c0092ce:	32f68b63          	beq	a3,a5,1c009604 <pos_libc_prf+0xe7a>
1c0092d2:	4732                	lw	a4,12(sp)
1c0092d4:	84ca                	mv	s1,s2
1c0092d6:	99ba                	add	s3,s3,a4
1c0092d8:	ff375b63          	ble	s3,a4,1c008ace <pos_libc_prf+0x344>
1c0092dc:	46b2                	lw	a3,12(sp)
1c0092de:	4595                	li	a1,5
1c0092e0:	00dc87b3          	add	a5,s9,a3
1c0092e4:	40f007b3          	neg	a5,a5
1c0092e8:	fa27b7b3          	p.bclr	a5,a5,29,2
1c0092ec:	00378613          	addi	a2,a5,3
1c0092f0:	fff98693          	addi	a3,s3,-1
1c0092f4:	04b67633          	p.maxu	a2,a2,a1
1c0092f8:	8e99                	sub	a3,a3,a4
1c0092fa:	40e985b3          	sub	a1,s3,a4
1c0092fe:	06c6e763          	bltu	a3,a2,1c00936c <pos_libc_prf+0xbe2>
1c009302:	863a                	mv	a2,a4
1c009304:	cf95                	beqz	a5,1c009340 <pos_libc_prf+0xbb6>
1c009306:	1990                	addi	a2,sp,240
1c009308:	00e606b3          	add	a3,a2,a4
1c00930c:	4742                	lw	a4,16(sp)
1c00930e:	f2e68a23          	sb	a4,-204(a3)
1c009312:	46b2                	lw	a3,12(sp)
1c009314:	00168613          	addi	a2,a3,1
1c009318:	0217a463          	p.beqimm	a5,1,1c009340 <pos_libc_prf+0xbb6>
1c00931c:	86ba                	mv	a3,a4
1c00931e:	1998                	addi	a4,sp,240
1c009320:	963a                	add	a2,a2,a4
1c009322:	4732                	lw	a4,12(sp)
1c009324:	f2d60a23          	sb	a3,-204(a2)
1c009328:	00270613          	addi	a2,a4,2
1c00932c:	0037ba63          	p.bneimm	a5,3,1c009340 <pos_libc_prf+0xbb6>
1c009330:	8736                	mv	a4,a3
1c009332:	1994                	addi	a3,sp,240
1c009334:	9636                	add	a2,a2,a3
1c009336:	46b2                	lw	a3,12(sp)
1c009338:	f2e60a23          	sb	a4,-204(a2)
1c00933c:	00368613          	addi	a2,a3,3
1c009340:	4732                	lw	a4,12(sp)
1c009342:	8d9d                	sub	a1,a1,a5
1c009344:	0025d693          	srli	a3,a1,0x2
1c009348:	97ba                	add	a5,a5,a4
1c00934a:	4742                	lw	a4,16(sp)
1c00934c:	97e6                	add	a5,a5,s9
1c00934e:	00e05557          	pv.add.sc.b	a0,zero,a4
1c009352:	34068663          	beqz	a3,1c00969e <pos_libc_prf+0xf14>
1c009356:	0046c0fb          	lp.setup	x1,a3,1c00935e <pos_libc_prf+0xbd4>
1c00935a:	00a7a22b          	p.sw	a0,4(a5!)
1c00935e:	0001                	nop
1c009360:	c205b7b3          	p.bclr	a5,a1,1,0
1c009364:	963e                	add	a2,a2,a5
1c009366:	c632                	sw	a2,12(sp)
1c009368:	f6b78263          	beq	a5,a1,1c008acc <pos_libc_prf+0x342>
1c00936c:	46b2                	lw	a3,12(sp)
1c00936e:	4742                	lw	a4,16(sp)
1c009370:	198c                	addi	a1,sp,240
1c009372:	00d587b3          	add	a5,a1,a3
1c009376:	f2e78a23          	sb	a4,-204(a5)
1c00937a:	00168793          	addi	a5,a3,1
1c00937e:	f537d763          	ble	s3,a5,1c008acc <pos_libc_prf+0x342>
1c009382:	97ae                	add	a5,a5,a1
1c009384:	f2e78a23          	sb	a4,-204(a5)
1c009388:	00268793          	addi	a5,a3,2
1c00938c:	f537d063          	ble	s3,a5,1c008acc <pos_libc_prf+0x342>
1c009390:	97ae                	add	a5,a5,a1
1c009392:	f2e78a23          	sb	a4,-204(a5)
1c009396:	00368793          	addi	a5,a3,3
1c00939a:	f337d963          	ble	s3,a5,1c008acc <pos_libc_prf+0x342>
1c00939e:	97ae                	add	a5,a5,a1
1c0093a0:	f2e78a23          	sb	a4,-204(a5)
1c0093a4:	00468793          	addi	a5,a3,4
1c0093a8:	f337d263          	ble	s3,a5,1c008acc <pos_libc_prf+0x342>
1c0093ac:	97ae                	add	a5,a5,a1
1c0093ae:	f2e78a23          	sb	a4,-204(a5)
1c0093b2:	00568a93          	addi	s5,a3,5
1c0093b6:	f13adb63          	ble	s3,s5,1c008acc <pos_libc_prf+0x342>
1c0093ba:	9aae                	add	s5,s5,a1
1c0093bc:	f2ea8a23          	sb	a4,-204(s5)
1c0093c0:	84ca                	mv	s1,s2
1c0093c2:	f0cff06f          	j	1c008ace <pos_libc_prf+0x344>
1c0093c6:	4301                	li	t1,0
1c0093c8:	8666                	mv	a2,s9
1c0093ca:	da0ff06f          	j	1c00896a <pos_libc_prf+0x1e0>
1c0093ce:	02414783          	lbu	a5,36(sp)
1c0093d2:	1054                	addi	a3,sp,36
1c0093d4:	4665                	li	a2,25
1c0093d6:	de078b63          	beqz	a5,1c0089cc <pos_libc_prf+0x242>
1c0093da:	fe078593          	addi	a1,a5,-32
1c0093de:	f9f78793          	addi	a5,a5,-97
1c0093e2:	0ff7f793          	andi	a5,a5,255
1c0093e6:	00f66963          	bltu	a2,a5,1c0093f8 <pos_libc_prf+0xc6e>
1c0093ea:	00b680ab          	p.sb	a1,1(a3!)
1c0093ee:	0006c783          	lbu	a5,0(a3)
1c0093f2:	f7e5                	bnez	a5,1c0093da <pos_libc_prf+0xc50>
1c0093f4:	dd8ff06f          	j	1c0089cc <pos_libc_prf+0x242>
1c0093f8:	0685                	addi	a3,a3,1
1c0093fa:	0006c783          	lbu	a5,0(a3)
1c0093fe:	fff1                	bnez	a5,1c0093da <pos_libc_prf+0xc50>
1c009400:	dccff06f          	j	1c0089cc <pos_libc_prf+0x242>
1c009404:	ee97c663          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c009408:	8c46                	mv	s8,a7
1c00940a:	de2ff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c00940e:	020102a3          	sb	zero,37(sp)
1c009412:	8c42                	mv	s8,a6
1c009414:	44b2                	lw	s1,12(sp)
1c009416:	d1fa2363          	p.beqimm	s4,-1,1c00891c <pos_libc_prf+0x192>
1c00941a:	02000693          	li	a3,32
1c00941e:	c836                	sw	a3,16(sp)
1c009420:	cfcff06f          	j	1c00891c <pos_libc_prf+0x192>
1c009424:	8566                	mv	a0,s9
1c009426:	86e6                	mv	a3,s9
1c009428:	fb6ff06f          	j	1c008bde <pos_libc_prf+0x454>
1c00942c:	4732                	lw	a4,12(sp)
1c00942e:	4e01                	li	t3,0
1c009430:	e319                	bnez	a4,1c009436 <pos_libc_prf+0xcac>
1c009432:	01403e33          	snez	t3,s4
1c009436:	5675                	li	a2,-3
1c009438:	001a0693          	addi	a3,s4,1
1c00943c:	00c84463          	blt	a6,a2,1c009444 <pos_libc_prf+0xcba>
1c009440:	1706d063          	ble	a6,a3,1c0095a0 <pos_libc_prf+0xe16>
1c009444:	47c1                	li	a5,16
1c009446:	04f6cf33          	p.min	t5,a3,a5
1c00944a:	06700693          	li	a3,103
1c00944e:	1f7d                	addi	t5,t5,-1
1c009450:	1ed48a63          	beq	s1,a3,1c009644 <pos_libc_prf+0xeba>
1c009454:	04500493          	li	s1,69
1c009458:	b2d9                	j	1c008e1e <pos_libc_prf+0x694>
1c00945a:	02b00793          	li	a5,43
1c00945e:	02f10223          	sb	a5,36(sp)
1c009462:	02510793          	addi	a5,sp,37
1c009466:	bb21                	j	1c00917e <pos_libc_prf+0x9f4>
1c009468:	8666                	mv	a2,s9
1c00946a:	1a084063          	bltz	a6,1c00960a <pos_libc_prf+0xe80>
1c00946e:	8ecd                	or	a3,a3,a1
1c009470:	fbf48793          	addi	a5,s1,-65
1c009474:	00360713          	addi	a4,a2,3
1c009478:	14069b63          	bnez	a3,1c0095ce <pos_libc_prf+0xe44>
1c00947c:	46e5                	li	a3,25
1c00947e:	1af6e563          	bltu	a3,a5,1c009628 <pos_libc_prf+0xe9e>
1c009482:	6795                	lui	a5,0x5
1c009484:	e4978793          	addi	a5,a5,-439 # 4e49 <__cluster_text_size+0x4e49>
1c009488:	00f61023          	sh	a5,0(a2)
1c00948c:	04600793          	li	a5,70
1c009490:	00f60123          	sb	a5,2(a2)
1c009494:	000601a3          	sb	zero,3(a2)
1c009498:	419704b3          	sub	s1,a4,s9
1c00949c:	bea9                	j	1c008ff6 <pos_libc_prf+0x86c>
1c00949e:	46d2                	lw	a3,20(sp)
1c0094a0:	14068463          	beqz	a3,1c0095e8 <pos_libc_prf+0xe5e>
1c0094a4:	02b00693          	li	a3,43
1c0094a8:	02d10223          	sb	a3,36(sp)
1c0094ac:	02510893          	addi	a7,sp,37
1c0094b0:	4801                	li	a6,0
1c0094b2:	4501                	li	a0,0
1c0094b4:	4681                	li	a3,0
1c0094b6:	4301                	li	t1,0
1c0094b8:	ba09                	j	1c008dca <pos_libc_prf+0x640>
1c0094ba:	02d00793          	li	a5,45
1c0094be:	02f10223          	sb	a5,36(sp)
1c0094c2:	800007b7          	lui	a5,0x80000
1c0094c6:	1af50963          	beq	a0,a5,1c009678 <pos_libc_prf+0xeee>
1c0094ca:	40a006b3          	neg	a3,a0
1c0094ce:	02510793          	addi	a5,sp,37
1c0094d2:	b175                	j	1c00917e <pos_libc_prf+0x9f4>
1c0094d4:	4a19                	li	s4,6
1c0094d6:	92d495e3          	bne	s1,a3,1c008e00 <pos_libc_prf+0x676>
1c0094da:	46b2                	lw	a3,12(sp)
1c0094dc:	57f5                	li	a5,-3
1c0094de:	0016ce13          	xori	t3,a3,1
1c0094e2:	14f85d63          	ble	a5,a6,1c00963c <pos_libc_prf+0xeb2>
1c0094e6:	06500493          	li	s1,101
1c0094ea:	4f19                	li	t5,6
1c0094ec:	ba0d                	j	1c008e1e <pos_libc_prf+0x694>
1c0094ee:	e097c163          	blt	a5,s1,1c008af0 <pos_libc_prf+0x366>
1c0094f2:	8c42                	mv	s8,a6
1c0094f4:	c602                	sw	zero,12(sp)
1c0094f6:	cf6ff06f          	j	1c0089ec <pos_libc_prf+0x262>
1c0094fa:	aa0a0be3          	beqz	s4,1c008fb0 <pos_libc_prf+0x826>
1c0094fe:	02e00593          	li	a1,46
1c009502:	00288613          	addi	a2,a7,2
1c009506:	00b880a3          	sb	a1,1(a7)
1c00950a:	bc91                	j	1c008f5e <pos_libc_prf+0x7d4>
1c00950c:	17005b63          	blez	a6,1c009682 <pos_libc_prf+0xef8>
1c009510:	9846                	add	a6,a6,a7
1c009512:	4ec1                	li	t4,16
1c009514:	03000f13          	li	t5,48
1c009518:	00269793          	slli	a5,a3,0x2
1c00951c:	01e6d593          	srli	a1,a3,0x1e
1c009520:	00251713          	slli	a4,a0,0x2
1c009524:	00d78633          	add	a2,a5,a3
1c009528:	8f4d                	or	a4,a4,a1
1c00952a:	972a                	add	a4,a4,a0
1c00952c:	00f637b3          	sltu	a5,a2,a5
1c009530:	97ba                	add	a5,a5,a4
1c009532:	0786                	slli	a5,a5,0x1
1c009534:	01f65713          	srli	a4,a2,0x1f
1c009538:	8fd9                	or	a5,a5,a4
1c00953a:	01c7d713          	srli	a4,a5,0x1c
1c00953e:	03070713          	addi	a4,a4,48
1c009542:	05d05963          	blez	t4,1c009594 <pos_libc_prf+0xe0a>
1c009546:	00e880ab          	p.sb	a4,1(a7!)
1c00954a:	10000737          	lui	a4,0x10000
1c00954e:	177d                	addi	a4,a4,-1
1c009550:	1efd                	addi	t4,t4,-1
1c009552:	00161693          	slli	a3,a2,0x1
1c009556:	00e7f533          	and	a0,a5,a4
1c00955a:	fb181fe3          	bne	a6,a7,1c009518 <pos_libc_prf+0xd8e>
1c00955e:	8642                	mv	a2,a6
1c009560:	4801                	li	a6,0
1c009562:	47b2                	lw	a5,12(sp)
1c009564:	e399                	bnez	a5,1c00956a <pos_libc_prf+0xde0>
1c009566:	b00a04e3          	beqz	s4,1c00906e <pos_libc_prf+0x8e4>
1c00956a:	00160f93          	addi	t6,a2,1
1c00956e:	001a0593          	addi	a1,s4,1
1c009572:	02e00893          	li	a7,46
1c009576:	01160023          	sb	a7,0(a2)
1c00957a:	837e                	mv	t1,t6
1c00957c:	962e                	add	a2,a2,a1
1c00957e:	03000593          	li	a1,48
1c009582:	aec304e3          	beq	t1,a2,1c00906a <pos_libc_prf+0x8e0>
1c009586:	0305                	addi	t1,t1,1
1c009588:	a8080be3          	beqz	a6,1c00901e <pos_libc_prf+0x894>
1c00958c:	feb30fa3          	sb	a1,-1(t1)
1c009590:	0805                	addi	a6,a6,1
1c009592:	bfc5                	j	1c009582 <pos_libc_prf+0xdf8>
1c009594:	01e880ab          	p.sb	t5,1(a7!)
1c009598:	f91810e3          	bne	a6,a7,1c009518 <pos_libc_prf+0xd8e>
1c00959c:	b7c9                	j	1c00955e <pos_libc_prf+0xdd4>
1c00959e:	4e01                	li	t3,0
1c0095a0:	014807b3          	add	a5,a6,s4
1c0095a4:	0e07c563          	bltz	a5,1c00968e <pos_libc_prf+0xf04>
1c0095a8:	4641                	li	a2,16
1c0095aa:	04c7cf33          	p.min	t5,a5,a2
1c0095ae:	1f7d                	addi	t5,t5,-1
1c0095b0:	06600493          	li	s1,102
1c0095b4:	860795e3          	bnez	a5,1c008e1e <pos_libc_prf+0x694>
1c0095b8:	4581                	li	a1,0
1c0095ba:	080006b7          	lui	a3,0x8000
1c0095be:	b0e9                	j	1c008e88 <pos_libc_prf+0x6fe>
1c0095c0:	02d00793          	li	a5,45
1c0095c4:	41000833          	neg	a6,a6
1c0095c8:	00f600a3          	sb	a5,1(a2)
1c0095cc:	b419                	j	1c008fd2 <pos_libc_prf+0x848>
1c0095ce:	46e5                	li	a3,25
1c0095d0:	06f6ee63          	bltu	a3,a5,1c00964c <pos_libc_prf+0xec2>
1c0095d4:	6791                	lui	a5,0x4
1c0095d6:	14e78793          	addi	a5,a5,334 # 414e <__cluster_text_size+0x414e>
1c0095da:	00f61023          	sh	a5,0(a2)
1c0095de:	04e00793          	li	a5,78
1c0095e2:	00f60123          	sb	a5,2(a2)
1c0095e6:	b57d                	j	1c009494 <pos_libc_prf+0xd0a>
1c0095e8:	47e2                	lw	a5,24(sp)
1c0095ea:	cfc5                	beqz	a5,1c0096a2 <pos_libc_prf+0xf18>
1c0095ec:	02000693          	li	a3,32
1c0095f0:	02d10223          	sb	a3,36(sp)
1c0095f4:	02510893          	addi	a7,sp,37
1c0095f8:	4801                	li	a6,0
1c0095fa:	4501                	li	a0,0
1c0095fc:	4681                	li	a3,0
1c0095fe:	4301                	li	t1,0
1c009600:	fcaff06f          	j	1c008dca <pos_libc_prf+0x640>
1c009604:	c602                	sw	zero,12(sp)
1c009606:	4732                	lw	a4,12(sp)
1c009608:	b9d1                	j	1c0092dc <pos_libc_prf+0xb52>
1c00960a:	02d00613          	li	a2,45
1c00960e:	02c10223          	sb	a2,36(sp)
1c009612:	02510613          	addi	a2,sp,37
1c009616:	bda1                	j	1c00946e <pos_libc_prf+0xce4>
1c009618:	02d00613          	li	a2,45
1c00961c:	02c10223          	sb	a2,36(sp)
1c009620:	02510893          	addi	a7,sp,37
1c009624:	ec6ff06f          	j	1c008cea <pos_libc_prf+0x560>
1c009628:	679d                	lui	a5,0x7
1c00962a:	e6978793          	addi	a5,a5,-407 # 6e69 <__cluster_text_size+0x6e69>
1c00962e:	00f61023          	sh	a5,0(a2)
1c009632:	06600793          	li	a5,102
1c009636:	00f60123          	sb	a5,2(a2)
1c00963a:	bda9                	j	1c009494 <pos_libc_prf+0xd0a>
1c00963c:	479d                	li	a5,7
1c00963e:	f707d1e3          	ble	a6,a5,1c0095a0 <pos_libc_prf+0xe16>
1c009642:	4f19                	li	t5,6
1c009644:	06500493          	li	s1,101
1c009648:	fd6ff06f          	j	1c008e1e <pos_libc_prf+0x694>
1c00964c:	6799                	lui	a5,0x6
1c00964e:	16e78793          	addi	a5,a5,366 # 616e <__cluster_text_size+0x616e>
1c009652:	00f61023          	sh	a5,0(a2)
1c009656:	06e00793          	li	a5,110
1c00965a:	00f60123          	sb	a5,2(a2)
1c00965e:	bd1d                	j	1c009494 <pos_libc_prf+0xd0a>
1c009660:	47e2                	lw	a5,24(sp)
1c009662:	88e6                	mv	a7,s9
1c009664:	e8078363          	beqz	a5,1c008cea <pos_libc_prf+0x560>
1c009668:	02000613          	li	a2,32
1c00966c:	02c10223          	sb	a2,36(sp)
1c009670:	02510893          	addi	a7,sp,37
1c009674:	e76ff06f          	j	1c008cea <pos_libc_prf+0x560>
1c009678:	800006b7          	lui	a3,0x80000
1c00967c:	02510793          	addi	a5,sp,37
1c009680:	bcfd                	j	1c00917e <pos_libc_prf+0x9f4>
1c009682:	03000593          	li	a1,48
1c009686:	00b88023          	sb	a1,0(a7)
1c00968a:	4ec1                	li	t4,16
1c00968c:	bdd9                	j	1c009562 <pos_libc_prf+0xdd8>
1c00968e:	06600493          	li	s1,102
1c009692:	b71d                	j	1c0095b8 <pos_libc_prf+0xe2e>
1c009694:	4685                	li	a3,1
1c009696:	bc4ff06f          	j	1c008a5a <pos_libc_prf+0x2d0>
1c00969a:	4605                	li	a2,1
1c00969c:	bcb9                	j	1c0090fa <pos_libc_prf+0x970>
1c00969e:	4685                	li	a3,1
1c0096a0:	b95d                	j	1c009356 <pos_libc_prf+0xbcc>
1c0096a2:	88e6                	mv	a7,s9
1c0096a4:	bf91                	j	1c0095f8 <pos_libc_prf+0xe6e>

1c0096a6 <pos_init_start>:
1c0096a6:	1141                	addi	sp,sp,-16
1c0096a8:	c422                	sw	s0,8(sp)
1c0096aa:	1c000437          	lui	s0,0x1c000
1c0096ae:	c606                	sw	ra,12(sp)
1c0096b0:	00840413          	addi	s0,s0,8 # 1c000008 <ctor_list>
1c0096b4:	c67fe0ef          	jal	ra,1c00831a <pos_soc_init>
1c0096b8:	2279                	jal	1c009846 <pos_irq_init>
1c0096ba:	2ac1                	jal	1c00988a <pos_soc_event_init>
1c0096bc:	20e5                	jal	1c0097a4 <pos_allocs_init>
1c0096be:	405c                	lw	a5,4(s0)
1c0096c0:	c791                	beqz	a5,1c0096cc <pos_init_start+0x26>
1c0096c2:	0421                	addi	s0,s0,8
1c0096c4:	9782                	jalr	a5
1c0096c6:	0044278b          	p.lw	a5,4(s0!)
1c0096ca:	ffed                	bnez	a5,1c0096c4 <pos_init_start+0x1e>
1c0096cc:	888ff0ef          	jal	ra,1c008754 <pos_io_start>
1c0096d0:	300467f3          	csrrsi	a5,mstatus,8
1c0096d4:	f1402573          	csrr	a0,mhartid
1c0096d8:	8515                	srai	a0,a0,0x5
1c0096da:	f2653533          	p.bclr	a0,a0,25,6
1c0096de:	47fd                	li	a5,31
1c0096e0:	00f50a63          	beq	a0,a5,1c0096f4 <pos_init_start+0x4e>
1c0096e4:	4422                	lw	s0,8(sp)
1c0096e6:	40b2                	lw	ra,12(sp)
1c0096e8:	1c0085b7          	lui	a1,0x1c008
1c0096ec:	13e58593          	addi	a1,a1,318 # 1c00813e <main>
1c0096f0:	0141                	addi	sp,sp,16
1c0096f2:	a405                	j	1c009912 <cluster_start>
1c0096f4:	40b2                	lw	ra,12(sp)
1c0096f6:	4422                	lw	s0,8(sp)
1c0096f8:	0141                	addi	sp,sp,16
1c0096fa:	8082                	ret

1c0096fc <pos_init_stop>:
1c0096fc:	1141                	addi	sp,sp,-16
1c0096fe:	c422                	sw	s0,8(sp)
1c009700:	1c000437          	lui	s0,0x1c000
1c009704:	c606                	sw	ra,12(sp)
1c009706:	01440413          	addi	s0,s0,20 # 1c000014 <dtor_list>
1c00970a:	84eff0ef          	jal	ra,1c008758 <pos_io_stop>
1c00970e:	405c                	lw	a5,4(s0)
1c009710:	c791                	beqz	a5,1c00971c <pos_init_stop+0x20>
1c009712:	0421                	addi	s0,s0,8
1c009714:	9782                	jalr	a5
1c009716:	0044278b          	p.lw	a5,4(s0!)
1c00971a:	ffed                	bnez	a5,1c009714 <pos_init_stop+0x18>
1c00971c:	40b2                	lw	ra,12(sp)
1c00971e:	4422                	lw	s0,8(sp)
1c009720:	0141                	addi	sp,sp,16
1c009722:	8082                	ret

1c009724 <pos_alloc_init>:
1c009724:	00758793          	addi	a5,a1,7
1c009728:	c407b7b3          	p.bclr	a5,a5,2,0
1c00972c:	40b785b3          	sub	a1,a5,a1
1c009730:	c11c                	sw	a5,0(a0)
1c009732:	8e0d                	sub	a2,a2,a1
1c009734:	00c05763          	blez	a2,1c009742 <pos_alloc_init+0x1e>
1c009738:	c4063633          	p.bclr	a2,a2,2,0
1c00973c:	c390                	sw	a2,0(a5)
1c00973e:	0007a223          	sw	zero,4(a5)
1c009742:	8082                	ret

1c009744 <pos_alloc>:
1c009744:	4110                	lw	a2,0(a0)
1c009746:	059d                	addi	a1,a1,7
1c009748:	c405b5b3          	p.bclr	a1,a1,2,0
1c00974c:	ca31                	beqz	a2,1c0097a0 <pos_alloc+0x5c>
1c00974e:	4218                	lw	a4,0(a2)
1c009750:	425c                	lw	a5,4(a2)
1c009752:	02b75963          	ble	a1,a4,1c009784 <pos_alloc+0x40>
1c009756:	cb81                	beqz	a5,1c009766 <pos_alloc+0x22>
1c009758:	4398                	lw	a4,0(a5)
1c00975a:	43d4                	lw	a3,4(a5)
1c00975c:	00b75763          	ble	a1,a4,1c00976a <pos_alloc+0x26>
1c009760:	863e                	mv	a2,a5
1c009762:	87b6                	mv	a5,a3
1c009764:	fbf5                	bnez	a5,1c009758 <pos_alloc+0x14>
1c009766:	853e                	mv	a0,a5
1c009768:	8082                	ret
1c00976a:	00b70a63          	beq	a4,a1,1c00977e <pos_alloc+0x3a>
1c00976e:	00b78533          	add	a0,a5,a1
1c009772:	8f0d                	sub	a4,a4,a1
1c009774:	c118                	sw	a4,0(a0)
1c009776:	c154                	sw	a3,4(a0)
1c009778:	c248                	sw	a0,4(a2)
1c00977a:	853e                	mv	a0,a5
1c00977c:	8082                	ret
1c00977e:	c254                	sw	a3,4(a2)
1c009780:	853e                	mv	a0,a5
1c009782:	8082                	ret
1c009784:	00e58b63          	beq	a1,a4,1c00979a <pos_alloc+0x56>
1c009788:	00b606b3          	add	a3,a2,a1
1c00978c:	8f0d                	sub	a4,a4,a1
1c00978e:	c2dc                	sw	a5,4(a3)
1c009790:	c298                	sw	a4,0(a3)
1c009792:	87b2                	mv	a5,a2
1c009794:	c114                	sw	a3,0(a0)
1c009796:	853e                	mv	a0,a5
1c009798:	8082                	ret
1c00979a:	c11c                	sw	a5,0(a0)
1c00979c:	87b2                	mv	a5,a2
1c00979e:	b7e1                	j	1c009766 <pos_alloc+0x22>
1c0097a0:	4781                	li	a5,0
1c0097a2:	b7d1                	j	1c009766 <pos_alloc+0x22>

1c0097a4 <pos_allocs_init>:
1c0097a4:	1141                	addi	sp,sp,-16
1c0097a6:	1c0015b7          	lui	a1,0x1c001
1c0097aa:	c606                	sw	ra,12(sp)
1c0097ac:	8a858793          	addi	a5,a1,-1880 # 1c0008a8 <__l2_priv0_end>
1c0097b0:	1c008637          	lui	a2,0x1c008
1c0097b4:	04c7cc63          	blt	a5,a2,1c00980c <pos_allocs_init+0x68>
1c0097b8:	4581                	li	a1,0
1c0097ba:	4601                	li	a2,0
1c0097bc:	1c001537          	lui	a0,0x1c001
1c0097c0:	89850513          	addi	a0,a0,-1896 # 1c000898 <pos_alloc_l2>
1c0097c4:	3785                	jal	1c009724 <pos_alloc_init>
1c0097c6:	1c00a5b7          	lui	a1,0x1c00a
1c0097ca:	9e858793          	addi	a5,a1,-1560 # 1c0099e8 <__l2_priv1_end>
1c0097ce:	1c010637          	lui	a2,0x1c010
1c0097d2:	02c7c963          	blt	a5,a2,1c009804 <pos_allocs_init+0x60>
1c0097d6:	4581                	li	a1,0
1c0097d8:	4601                	li	a2,0
1c0097da:	1c001537          	lui	a0,0x1c001
1c0097de:	89c50513          	addi	a0,a0,-1892 # 1c00089c <pos_alloc_l2+0x4>
1c0097e2:	3789                	jal	1c009724 <pos_alloc_init>
1c0097e4:	100005b7          	lui	a1,0x10000
1c0097e8:	40b2                	lw	ra,12(sp)
1c0097ea:	00858793          	addi	a5,a1,8 # 10000008 <__l2_shared_end>
1c0097ee:	1c080637          	lui	a2,0x1c080
1c0097f2:	1c001537          	lui	a0,0x1c001
1c0097f6:	8e1d                	sub	a2,a2,a5
1c0097f8:	00858593          	addi	a1,a1,8
1c0097fc:	8a050513          	addi	a0,a0,-1888 # 1c0008a0 <pos_alloc_l2+0x8>
1c009800:	0141                	addi	sp,sp,16
1c009802:	b70d                	j	1c009724 <pos_alloc_init>
1c009804:	8e1d                	sub	a2,a2,a5
1c009806:	9e858593          	addi	a1,a1,-1560
1c00980a:	bfc1                	j	1c0097da <pos_allocs_init+0x36>
1c00980c:	8e1d                	sub	a2,a2,a5
1c00980e:	8a858593          	addi	a1,a1,-1880
1c009812:	b76d                	j	1c0097bc <pos_allocs_init+0x18>

1c009814 <alloc_init_l1>:
1c009814:	100007b7          	lui	a5,0x10000
1c009818:	01651593          	slli	a1,a0,0x16
1c00981c:	00878793          	addi	a5,a5,8 # 10000008 <__l2_shared_end>
1c009820:	95be                	add	a1,a1,a5
1c009822:	1c0017b7          	lui	a5,0x1c001
1c009826:	050a                	slli	a0,a0,0x2
1c009828:	6641                	lui	a2,0x10
1c00982a:	89478793          	addi	a5,a5,-1900 # 1c000894 <pos_alloc_l1>
1c00982e:	ff860613          	addi	a2,a2,-8 # fff8 <__l1_heap_size>
1c009832:	953e                	add	a0,a0,a5
1c009834:	bdc5                	j	1c009724 <pos_alloc_init>

1c009836 <pi_l1_malloc>:
1c009836:	1c0017b7          	lui	a5,0x1c001
1c00983a:	050a                	slli	a0,a0,0x2
1c00983c:	89478793          	addi	a5,a5,-1900 # 1c000894 <pos_alloc_l1>
1c009840:	953e                	add	a0,a0,a5
1c009842:	b709                	j	1c009744 <pos_alloc>

1c009844 <__rt_handle_illegal_instr>:
1c009844:	8082                	ret

1c009846 <pos_irq_init>:
1c009846:	f14027f3          	csrr	a5,mhartid
1c00984a:	477d                	li	a4,31
1c00984c:	ca5797b3          	p.extractu	a5,a5,5,5
1c009850:	00e78f63          	beq	a5,a4,1c00986e <pos_irq_init+0x28>
1c009854:	002047b7          	lui	a5,0x204
1c009858:	577d                	li	a4,-1
1c00985a:	cb98                	sw	a4,16(a5)
1c00985c:	1c0087b7          	lui	a5,0x1c008
1c009860:	00078793          	mv	a5,a5
1c009864:	c007c7b3          	p.bset	a5,a5,0,0
1c009868:	30579073          	csrw	mtvec,a5
1c00986c:	8082                	ret
1c00986e:	1a10a7b7          	lui	a5,0x1a10a
1c009872:	577d                	li	a4,-1
1c009874:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c009878:	1c0087b7          	lui	a5,0x1c008
1c00987c:	00078793          	mv	a5,a5
1c009880:	c007c7b3          	p.bset	a5,a5,0,0
1c009884:	30579073          	csrw	mtvec,a5
1c009888:	8082                	ret

1c00988a <pos_soc_event_init>:
1c00988a:	1a1067b7          	lui	a5,0x1a106
1c00988e:	577d                	li	a4,-1
1c009890:	00478693          	addi	a3,a5,4 # 1a106004 <__l2_shared_end+0xa105ffc>
1c009894:	c298                	sw	a4,0(a3)
1c009896:	00878693          	addi	a3,a5,8
1c00989a:	c298                	sw	a4,0(a3)
1c00989c:	00c78693          	addi	a3,a5,12
1c0098a0:	c298                	sw	a4,0(a3)
1c0098a2:	01078693          	addi	a3,a5,16
1c0098a6:	c298                	sw	a4,0(a3)
1c0098a8:	01478693          	addi	a3,a5,20
1c0098ac:	c298                	sw	a4,0(a3)
1c0098ae:	01878693          	addi	a3,a5,24
1c0098b2:	c298                	sw	a4,0(a3)
1c0098b4:	01c78693          	addi	a3,a5,28
1c0098b8:	c298                	sw	a4,0(a3)
1c0098ba:	02078793          	addi	a5,a5,32
1c0098be:	c398                	sw	a4,0(a5)
1c0098c0:	8082                	ret

1c0098c2 <cluster_entry_stub>:
1c0098c2:	1141                	addi	sp,sp,-16
1c0098c4:	c606                	sw	ra,12(sp)
1c0098c6:	002047b7          	lui	a5,0x204
1c0098ca:	00070737          	lui	a4,0x70
1c0098ce:	c798                	sw	a4,8(a5)
1c0098d0:	0ff00713          	li	a4,255
1c0098d4:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c0098d8:	00e7a023          	sw	a4,0(a5)
1c0098dc:	00e7a623          	sw	a4,12(a5)
1c0098e0:	1c0017b7          	lui	a5,0x1c001
1c0098e4:	8a47a783          	lw	a5,-1884(a5) # 1c0008a4 <cluster_entry>
1c0098e8:	9782                	jalr	a5
1c0098ea:	f14027f3          	csrr	a5,mhartid
1c0098ee:	f457b7b3          	p.bclr	a5,a5,26,5
1c0098f2:	eb89                	bnez	a5,1c009904 <cluster_entry_stub+0x42>
1c0098f4:	1c001737          	lui	a4,0x1c001
1c0098f8:	1c0017b7          	lui	a5,0x1c001
1c0098fc:	86a72a23          	sw	a0,-1932(a4) # 1c000874 <cluster_retval>
1c009900:	8607ac23          	sw	zero,-1928(a5) # 1c000878 <cluster_running>
1c009904:	002047b7          	lui	a5,0x204
1c009908:	577d                	li	a4,-1
1c00990a:	c3d8                	sw	a4,4(a5)
1c00990c:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c009910:	a001                	j	1c009910 <cluster_entry_stub+0x4e>

1c009912 <cluster_start>:
1c009912:	1141                	addi	sp,sp,-16
1c009914:	1c0017b7          	lui	a5,0x1c001
1c009918:	c226                	sw	s1,4(sp)
1c00991a:	84aa                	mv	s1,a0
1c00991c:	4509                	li	a0,2
1c00991e:	8ab7a223          	sw	a1,-1884(a5) # 1c0008a4 <cluster_entry>
1c009922:	c606                	sw	ra,12(sp)
1c009924:	c422                	sw	s0,8(sp)
1c009926:	8ddfe0ef          	jal	ra,1c008202 <pos_fll_init>
1c00992a:	8526                	mv	a0,s1
1c00992c:	35e5                	jal	1c009814 <alloc_init_l1>
1c00992e:	04048413          	addi	s0,s1,64
1c009932:	00201737          	lui	a4,0x201
1c009936:	40070713          	addi	a4,a4,1024 # 201400 <__l1_heap_size+0x1f1408>
1c00993a:	045a                	slli	s0,s0,0x16
1c00993c:	56fd                	li	a3,-1
1c00993e:	f14027f3          	csrr	a5,mhartid
1c009942:	00d46723          	p.sw	a3,a4(s0)
1c009946:	ca5797b3          	p.extractu	a5,a5,5,5
1c00994a:	477d                	li	a4,31
1c00994c:	00e78f63          	beq	a5,a4,1c00996a <cluster_start+0x58>
1c009950:	002047b7          	lui	a5,0x204
1c009954:	00070737          	lui	a4,0x70
1c009958:	c798                	sw	a4,8(a5)
1c00995a:	0ff00713          	li	a4,255
1c00995e:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c009962:	00e7a023          	sw	a4,0(a5)
1c009966:	00e7a623          	sw	a4,12(a5)
1c00996a:	8526                	mv	a0,s1
1c00996c:	3565                	jal	1c009814 <alloc_init_l1>
1c00996e:	6591                	lui	a1,0x4
1c009970:	8526                	mv	a0,s1
1c009972:	35d1                	jal	1c009836 <pi_l1_malloc>
1c009974:	100007b7          	lui	a5,0x10000
1c009978:	00a7a223          	sw	a0,4(a5) # 10000004 <cluster_stacks>
1c00997c:	c12d                	beqz	a0,1c0099de <cluster_start+0xcc>
1c00997e:	1c001737          	lui	a4,0x1c001
1c009982:	4685                	li	a3,1
1c009984:	86d72c23          	sw	a3,-1928(a4) # 1c000878 <cluster_running>
1c009988:	002007b7          	lui	a5,0x200
1c00998c:	1c008737          	lui	a4,0x1c008
1c009990:	08070713          	addi	a4,a4,128 # 1c008080 <_start>
1c009994:	04078693          	addi	a3,a5,64 # 200040 <__l1_heap_size+0x1f0048>
1c009998:	00e466a3          	p.sw	a4,a3(s0)
1c00999c:	04478693          	addi	a3,a5,68
1c0099a0:	00e466a3          	p.sw	a4,a3(s0)
1c0099a4:	04878693          	addi	a3,a5,72
1c0099a8:	00e466a3          	p.sw	a4,a3(s0)
1c0099ac:	04c78693          	addi	a3,a5,76
1c0099b0:	00e466a3          	p.sw	a4,a3(s0)
1c0099b4:	05078693          	addi	a3,a5,80
1c0099b8:	00e466a3          	p.sw	a4,a3(s0)
1c0099bc:	05478693          	addi	a3,a5,84
1c0099c0:	00e466a3          	p.sw	a4,a3(s0)
1c0099c4:	05878693          	addi	a3,a5,88
1c0099c8:	00e466a3          	p.sw	a4,a3(s0)
1c0099cc:	05c78693          	addi	a3,a5,92
1c0099d0:	00e466a3          	p.sw	a4,a3(s0)
1c0099d4:	07a1                	addi	a5,a5,8
1c0099d6:	0ff00713          	li	a4,255
1c0099da:	00e467a3          	p.sw	a4,a5(s0)
1c0099de:	40b2                	lw	ra,12(sp)
1c0099e0:	4422                	lw	s0,8(sp)
1c0099e2:	4492                	lw	s1,4(sp)
1c0099e4:	0141                	addi	sp,sp,16
1c0099e6:	8082                	ret

riscv32-unknown-elf-objdump -Mmarch=rv32imcxgap9 -d /scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/reg_access/all_reg_rw_i2c/build/test/test

/scratch/lvalente/project/open_pulp/pulp/regression_tests/peripherals/reg_access/all_reg_rw_i2c/build/test/test:     file format elf32-littleriscv


Disassembly of section .vectors:

1c008000 <__irq_vector_base>:
1c008000:	0610106f          	j	1c009860 <__rt_handle_illegal_instr>
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
1c008084:	7dc0106f          	j	1c009860 <__rt_handle_illegal_instr>

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
1c0080b4:	02b0106f          	j	1c0098de <cluster_entry_stub>

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
1c00811a:	5a8010ef          	jal	ra,1c0096c2 <pos_init_start>
1c00811e:	00000513          	li	a0,0
1c008122:	00000593          	li	a1,0
1c008126:	00000397          	auipc	t2,0x0
1c00812a:	01838393          	addi	t2,t2,24 # 1c00813e <main>
1c00812e:	000380e7          	jalr	t2
1c008132:	842a                	mv	s0,a0
1c008134:	5e4010ef          	jal	ra,1c009718 <pos_init_stop>
1c008138:	8522                	mv	a0,s0
1c00813a:	624000ef          	jal	ra,1c00875e <exit>

1c00813e <main>:
1c00813e:	1c0007b7          	lui	a5,0x1c000
1c008142:	01c7a783          	lw	a5,28(a5) # 1c00001c <__DTOR_END__>
1c008146:	715d                	addi	sp,sp,-80
1c008148:	c002                	sw	zero,0(sp)
1c00814a:	00f120a3          	sw	a5,1(sp)
1c00814e:	1c0007b7          	lui	a5,0x1c000
1c008152:	0207a783          	lw	a5,32(a5) # 1c000020 <__DTOR_END__+0x4>
1c008156:	c402                	sw	zero,8(sp)
1c008158:	c2a6                	sw	s1,68(sp)
1c00815a:	00f122a3          	sw	a5,5(sp)
1c00815e:	1a1024b7          	lui	s1,0x1a102
1c008162:	02400793          	li	a5,36
1c008166:	c0ca                	sw	s2,64(sp)
1c008168:	de4e                	sw	s3,60(sp)
1c00816a:	dc52                	sw	s4,56(sp)
1c00816c:	da56                	sw	s5,52(sp)
1c00816e:	d65e                	sw	s7,44(sp)
1c008170:	d462                	sw	s8,40(sp)
1c008172:	d266                	sw	s9,36(sp)
1c008174:	d06a                	sw	s10,32(sp)
1c008176:	c686                	sw	ra,76(sp)
1c008178:	c4a2                	sw	s0,72(sp)
1c00817a:	d85a                	sw	s6,48(sp)
1c00817c:	ce6e                	sw	s11,28(sp)
1c00817e:	00011623          	sh	zero,12(sp)
1c008182:	00f104a3          	sb	a5,9(sp)
1c008186:	18048493          	addi	s1,s1,384 # 1a102180 <__l2_shared_end+0xa102178>
1c00818a:	4b81                	li	s7,0
1c00818c:	1c000d37          	lui	s10,0x1c000
1c008190:	00a10a93          	addi	s5,sp,10
1c008194:	1c000a37          	lui	s4,0x1c000
1c008198:	1c0009b7          	lui	s3,0x1c000
1c00819c:	1a102c37          	lui	s8,0x1a102
1c0081a0:	4c85                	li	s9,1
1c0081a2:	597d                	li	s2,-1
1c0081a4:	000c2783          	lw	a5,0(s8) # 1a102000 <__l2_shared_end+0xa101ff8>
1c0081a8:	002b8b13          	addi	s6,s7,2
1c0081ac:	016c9b33          	sll	s6,s9,s6
1c0081b0:	00fb67b3          	or	a5,s6,a5
1c0081b4:	00fc2023          	sw	a5,0(s8)
1c0081b8:	85de                	mv	a1,s7
1c0081ba:	024d0513          	addi	a0,s10,36 # 1c000024 <__DTOR_END__+0x8>
1c0081be:	2b6d                	jal	1c008778 <printf>
1c0081c0:	8d8a                	mv	s11,sp
1c0081c2:	001dc40b          	p.lbu	s0,1(s11!)
1c0081c6:	55fd                	li	a1,-1
1c0081c8:	030a0513          	addi	a0,s4,48 # 1c000030 <__DTOR_END__+0x14>
1c0081cc:	9426                	add	s0,s0,s1
1c0081ce:	8622                	mv	a2,s0
1c0081d0:	01242023          	sw	s2,0(s0)
1c0081d4:	2355                	jal	1c008778 <printf>
1c0081d6:	400c                	lw	a1,0(s0)
1c0081d8:	8622                	mv	a2,s0
1c0081da:	04098513          	addi	a0,s3,64 # 1c000040 <__DTOR_END__+0x24>
1c0081de:	2b69                	jal	1c008778 <printf>
1c0081e0:	ffba91e3          	bne	s5,s11,1c0081c2 <main+0x84>
1c0081e4:	000c2783          	lw	a5,0(s8)
1c0081e8:	fffb4b13          	not	s6,s6
1c0081ec:	0b85                	addi	s7,s7,1
1c0081ee:	00fb7b33          	and	s6,s6,a5
1c0081f2:	016c2023          	sw	s6,0(s8)
1c0081f6:	08048493          	addi	s1,s1,128
1c0081fa:	fa3bb5e3          	p.bneimm	s7,3,1c0081a4 <main+0x66>
1c0081fe:	40b6                	lw	ra,76(sp)
1c008200:	4426                	lw	s0,72(sp)
1c008202:	4496                	lw	s1,68(sp)
1c008204:	4906                	lw	s2,64(sp)
1c008206:	59f2                	lw	s3,60(sp)
1c008208:	5a62                	lw	s4,56(sp)
1c00820a:	5ad2                	lw	s5,52(sp)
1c00820c:	5b42                	lw	s6,48(sp)
1c00820e:	5bb2                	lw	s7,44(sp)
1c008210:	5c22                	lw	s8,40(sp)
1c008212:	5c92                	lw	s9,36(sp)
1c008214:	5d02                	lw	s10,32(sp)
1c008216:	4df2                	lw	s11,28(sp)
1c008218:	4501                	li	a0,0
1c00821a:	6161                	addi	sp,sp,80
1c00821c:	8082                	ret

1c00821e <pos_fll_init>:
1c00821e:	00451613          	slli	a2,a0,0x4
1c008222:	85aa                	mv	a1,a0
1c008224:	00460813          	addi	a6,a2,4
1c008228:	1a1006b7          	lui	a3,0x1a100
1c00822c:	2106f783          	p.lw	a5,a6(a3)
1c008230:	873e                	mv	a4,a5
1c008232:	0407c163          	bltz	a5,1c008274 <pos_fll_init+0x56>
1c008236:	00860313          	addi	t1,a2,8
1c00823a:	2066f883          	p.lw	a7,t1(a3)
1c00823e:	4519                	li	a0,6
1c008240:	caa528b3          	p.insert	a7,a0,5,10
1c008244:	05000513          	li	a0,80
1c008248:	d70528b3          	p.insert	a7,a0,11,16
1c00824c:	1a100537          	lui	a0,0x1a100
1c008250:	01156323          	p.sw	a7,t1(a0)
1c008254:	0631                	addi	a2,a2,12
1c008256:	20c6f683          	p.lw	a3,a2(a3)
1c00825a:	14c00893          	li	a7,332
1c00825e:	d308a6b3          	p.insert	a3,a7,9,16
1c008262:	00d56623          	p.sw	a3,a2(a0)
1c008266:	4685                	li	a3,1
1c008268:	c1e6a733          	p.insert	a4,a3,0,30
1c00826c:	c1f6a733          	p.insert	a4,a3,0,31
1c008270:	00e56823          	p.sw	a4,a6(a0)
1c008274:	1c0016b7          	lui	a3,0x1c001
1c008278:	00259893          	slli	a7,a1,0x2
1c00827c:	87c68693          	addi	a3,a3,-1924 # 1c00087c <pos_fll_freq>
1c008280:	01168633          	add	a2,a3,a7
1c008284:	4208                	lw	a0,0(a2)
1c008286:	e115                	bnez	a0,1c0082aa <pos_fll_init+0x8c>
1c008288:	1007d7b3          	p.exthz	a5,a5
1c00828c:	c7a71733          	p.extractu	a4,a4,3,26
1c008290:	07be                	slli	a5,a5,0xf
1c008292:	177d                	addi	a4,a4,-1
1c008294:	00e7d533          	srl	a0,a5,a4
1c008298:	1c0017b7          	lui	a5,0x1c001
1c00829c:	c208                	sw	a0,0(a2)
1c00829e:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c0082a2:	4705                	li	a4,1
1c0082a4:	00e7c5a3          	p.sb	a4,a1(a5)
1c0082a8:	8082                	ret
1c0082aa:	10051733          	p.fl1	a4,a0
1c0082ae:	47f5                	li	a5,29
1c0082b0:	82e7b75b          	p.subun	a4,a5,a4,1
1c0082b4:	e731                	bnez	a4,1c008300 <pos_fll_init+0xe2>
1c0082b6:	4f09                	li	t5,2
1c0082b8:	4e05                	li	t3,1
1c0082ba:	4705                	li	a4,1
1c0082bc:	1c0017b7          	lui	a5,0x1c001
1c0082c0:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c0082c4:	00e51333          	sll	t1,a0,a4
1c0082c8:	00b78eb3          	add	t4,a5,a1
1c0082cc:	dc033633          	p.bclr	a2,t1,14,0
1c0082d0:	000ece83          	lbu	t4,0(t4)
1c0082d4:	c0ee265b          	p.addunr	a2,t3,a4
1c0082d8:	00c6e8a3          	p.sw	a2,a7(a3)
1c0082dc:	fc0e83e3          	beqz	t4,1c0082a2 <pos_fll_init+0x84>
1c0082e0:	1a1006b7          	lui	a3,0x1a100
1c0082e4:	2106f703          	p.lw	a4,a6(a3)
1c0082e8:	00f35313          	srli	t1,t1,0xf
1c0082ec:	de032733          	p.insert	a4,t1,15,0
1c0082f0:	c7af2733          	p.insert	a4,t5,3,26
1c0082f4:	00e6e823          	p.sw	a4,a6(a3)
1c0082f8:	4705                	li	a4,1
1c0082fa:	00e7c5a3          	p.sb	a4,a1(a5)
1c0082fe:	8082                	ret
1c008300:	fff70793          	addi	a5,a4,-1
1c008304:	4e05                	li	t3,1
1c008306:	00fe1e33          	sll	t3,t3,a5
1c00830a:	00170f13          	addi	t5,a4,1
1c00830e:	b77d                	j	1c0082bc <pos_fll_init+0x9e>

1c008310 <pos_fll_constructor>:
1c008310:	1c0016b7          	lui	a3,0x1c001
1c008314:	1c0017b7          	lui	a5,0x1c001
1c008318:	87c68713          	addi	a4,a3,-1924 # 1c00087c <pos_fll_freq>
1c00831c:	87078793          	addi	a5,a5,-1936 # 1c000870 <stack>
1c008320:	8606ae23          	sw	zero,-1924(a3)
1c008324:	00072223          	sw	zero,4(a4)
1c008328:	00072423          	sw	zero,8(a4)
1c00832c:	00079023          	sh	zero,0(a5)
1c008330:	00078123          	sb	zero,2(a5)
1c008334:	8082                	ret

1c008336 <pos_soc_init>:
1c008336:	1141                	addi	sp,sp,-16
1c008338:	c606                	sw	ra,12(sp)
1c00833a:	c422                	sw	s0,8(sp)
1c00833c:	3fd1                	jal	1c008310 <pos_fll_constructor>
1c00833e:	4501                	li	a0,0
1c008340:	3df9                	jal	1c00821e <pos_fll_init>
1c008342:	1c001437          	lui	s0,0x1c001
1c008346:	88a42423          	sw	a0,-1912(s0) # 1c000888 <pos_freq_domains>
1c00834a:	4505                	li	a0,1
1c00834c:	3dc9                	jal	1c00821e <pos_fll_init>
1c00834e:	88840413          	addi	s0,s0,-1912
1c008352:	c408                	sw	a0,8(s0)
1c008354:	4509                	li	a0,2
1c008356:	35e1                	jal	1c00821e <pos_fll_init>
1c008358:	c048                	sw	a0,4(s0)
1c00835a:	40b2                	lw	ra,12(sp)
1c00835c:	4422                	lw	s0,8(sp)
1c00835e:	0141                	addi	sp,sp,16
1c008360:	8082                	ret

1c008362 <pos_wait_forever>:
1c008362:	f14027f3          	csrr	a5,mhartid
1c008366:	477d                	li	a4,31
1c008368:	ca5797b3          	p.extractu	a5,a5,5,5
1c00836c:	00e78963          	beq	a5,a4,1c00837e <pos_wait_forever+0x1c>
1c008370:	002047b7          	lui	a5,0x204
1c008374:	577d                	li	a4,-1
1c008376:	c3d8                	sw	a4,4(a5)
1c008378:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c00837c:	a001                	j	1c00837c <pos_wait_forever+0x1a>
1c00837e:	1a10a7b7          	lui	a5,0x1a10a
1c008382:	577d                	li	a4,-1
1c008384:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c008388:	10500073          	wfi
1c00838c:	10500073          	wfi
1c008390:	bfe5                	j	1c008388 <pos_wait_forever+0x26>

1c008392 <memcpy>:
1c008392:	00a5e7b3          	or	a5,a1,a0
1c008396:	fa27b7b3          	p.bclr	a5,a5,29,2
1c00839a:	882a                	mv	a6,a0
1c00839c:	10078163          	beqz	a5,1c00849e <memcpy+0x10c>
1c0083a0:	12060263          	beqz	a2,1c0084c4 <memcpy+0x132>
1c0083a4:	00458793          	addi	a5,a1,4
1c0083a8:	00450693          	addi	a3,a0,4 # 1a100004 <__l2_shared_end+0xa0ffffc>
1c0083ac:	04a7b7b3          	p.sletu	a5,a5,a0
1c0083b0:	04b6b6b3          	p.sletu	a3,a3,a1
1c0083b4:	873e                	mv	a4,a5
1c0083b6:	87b6                	mv	a5,a3
1c0083b8:	8fd9                	or	a5,a5,a4
1c0083ba:	0ff7f793          	andi	a5,a5,255
1c0083be:	cbe9                	beqz	a5,1c008490 <memcpy+0xfe>
1c0083c0:	00863793          	sltiu	a5,a2,8
1c0083c4:	0017c793          	xori	a5,a5,1
1c0083c8:	0ff7f793          	andi	a5,a5,255
1c0083cc:	c3f1                	beqz	a5,1c008490 <memcpy+0xfe>
1c0083ce:	40b007b3          	neg	a5,a1
1c0083d2:	fa27b7b3          	p.bclr	a5,a5,29,2
1c0083d6:	fff60313          	addi	t1,a2,-1
1c0083da:	c3ed                	beqz	a5,1c0084bc <memcpy+0x12a>
1c0083dc:	0005c703          	lbu	a4,0(a1)
1c0083e0:	00158893          	addi	a7,a1,1
1c0083e4:	00150813          	addi	a6,a0,1
1c0083e8:	00e50023          	sb	a4,0(a0)
1c0083ec:	0217a863          	p.beqimm	a5,1,1c00841c <memcpy+0x8a>
1c0083f0:	0015c703          	lbu	a4,1(a1)
1c0083f4:	00258893          	addi	a7,a1,2
1c0083f8:	00250813          	addi	a6,a0,2
1c0083fc:	00e500a3          	sb	a4,1(a0)
1c008400:	ffe60313          	addi	t1,a2,-2
1c008404:	0037bc63          	p.bneimm	a5,3,1c00841c <memcpy+0x8a>
1c008408:	0025c703          	lbu	a4,2(a1)
1c00840c:	00358893          	addi	a7,a1,3
1c008410:	00350813          	addi	a6,a0,3
1c008414:	00e50123          	sb	a4,2(a0)
1c008418:	ffd60313          	addi	t1,a2,-3
1c00841c:	8e1d                	sub	a2,a2,a5
1c00841e:	00265713          	srli	a4,a2,0x2
1c008422:	00f506b3          	add	a3,a0,a5
1c008426:	95be                	add	a1,a1,a5
1c008428:	cf59                	beqz	a4,1c0084c6 <memcpy+0x134>
1c00842a:	004740fb          	lp.setup	x1,a4,1c008432 <memcpy+0xa0>
1c00842e:	0045a78b          	p.lw	a5,4(a1!)
1c008432:	00f6a22b          	p.sw	a5,4(a3!)
1c008436:	c20635b3          	p.bclr	a1,a2,1,0
1c00843a:	40b306b3          	sub	a3,t1,a1
1c00843e:	00b807b3          	add	a5,a6,a1
1c008442:	00b88733          	add	a4,a7,a1
1c008446:	04b60b63          	beq	a2,a1,1c00849c <memcpy+0x10a>
1c00844a:	00074603          	lbu	a2,0(a4)
1c00844e:	00c78023          	sb	a2,0(a5)
1c008452:	0416a563          	p.beqimm	a3,1,1c00849c <memcpy+0x10a>
1c008456:	00174603          	lbu	a2,1(a4)
1c00845a:	00c780a3          	sb	a2,1(a5)
1c00845e:	0226af63          	p.beqimm	a3,2,1c00849c <memcpy+0x10a>
1c008462:	00274603          	lbu	a2,2(a4)
1c008466:	00c78123          	sb	a2,2(a5)
1c00846a:	0236a963          	p.beqimm	a3,3,1c00849c <memcpy+0x10a>
1c00846e:	00374603          	lbu	a2,3(a4)
1c008472:	00c781a3          	sb	a2,3(a5)
1c008476:	0246a363          	p.beqimm	a3,4,1c00849c <memcpy+0x10a>
1c00847a:	00474603          	lbu	a2,4(a4)
1c00847e:	00c78223          	sb	a2,4(a5)
1c008482:	0056ad63          	p.beqimm	a3,5,1c00849c <memcpy+0x10a>
1c008486:	00574703          	lbu	a4,5(a4)
1c00848a:	00e782a3          	sb	a4,5(a5)
1c00848e:	8082                	ret
1c008490:	004640fb          	lp.setup	x1,a2,1c008498 <memcpy+0x106>
1c008494:	0015c78b          	p.lbu	a5,1(a1!)
1c008498:	00f800ab          	p.sb	a5,1(a6!)
1c00849c:	8082                	ret
1c00849e:	fa2637b3          	p.bclr	a5,a2,29,2
1c0084a2:	f389                	bnez	a5,1c0083a4 <memcpy+0x12>
1c0084a4:	de65                	beqz	a2,1c00849c <memcpy+0x10a>
1c0084a6:	ffc60793          	addi	a5,a2,-4
1c0084aa:	8389                	srli	a5,a5,0x2
1c0084ac:	0785                	addi	a5,a5,1
1c0084ae:	0047c0fb          	lp.setup	x1,a5,1c0084b6 <memcpy+0x124>
1c0084b2:	0045a70b          	p.lw	a4,4(a1!)
1c0084b6:	00e8222b          	p.sw	a4,4(a6!)
1c0084ba:	8082                	ret
1c0084bc:	88ae                	mv	a7,a1
1c0084be:	882a                	mv	a6,a0
1c0084c0:	8332                	mv	t1,a2
1c0084c2:	bfa9                	j	1c00841c <memcpy+0x8a>
1c0084c4:	8082                	ret
1c0084c6:	4705                	li	a4,1
1c0084c8:	b78d                	j	1c00842a <memcpy+0x98>

1c0084ca <memmove>:
1c0084ca:	40b507b3          	sub	a5,a0,a1
1c0084ce:	0ec7ec63          	bltu	a5,a2,1c0085c6 <memmove+0xfc>
1c0084d2:	20060463          	beqz	a2,1c0086da <memmove+0x210>
1c0084d6:	00450793          	addi	a5,a0,4
1c0084da:	00458693          	addi	a3,a1,4
1c0084de:	04b7b7b3          	p.sletu	a5,a5,a1
1c0084e2:	04a6b6b3          	p.sletu	a3,a3,a0
1c0084e6:	873e                	mv	a4,a5
1c0084e8:	87b6                	mv	a5,a3
1c0084ea:	8fd9                	or	a5,a5,a4
1c0084ec:	0ff7f793          	andi	a5,a5,255
1c0084f0:	1c078d63          	beqz	a5,1c0086ca <memmove+0x200>
1c0084f4:	00863793          	sltiu	a5,a2,8
1c0084f8:	0017c793          	xori	a5,a5,1
1c0084fc:	0ff7f793          	andi	a5,a5,255
1c008500:	1c078563          	beqz	a5,1c0086ca <memmove+0x200>
1c008504:	40b007b3          	neg	a5,a1
1c008508:	fa27b7b3          	p.bclr	a5,a5,29,2
1c00850c:	fff60313          	addi	t1,a2,-1
1c008510:	88ae                	mv	a7,a1
1c008512:	1e078363          	beqz	a5,1c0086f8 <memmove+0x22e>
1c008516:	0018c70b          	p.lbu	a4,1(a7!)
1c00851a:	882a                	mv	a6,a0
1c00851c:	00e800ab          	p.sb	a4,1(a6!)
1c008520:	0217a863          	p.beqimm	a5,1,1c008550 <memmove+0x86>
1c008524:	0015c703          	lbu	a4,1(a1)
1c008528:	00250813          	addi	a6,a0,2
1c00852c:	00258893          	addi	a7,a1,2
1c008530:	00e500a3          	sb	a4,1(a0)
1c008534:	ffe60313          	addi	t1,a2,-2
1c008538:	0037bc63          	p.bneimm	a5,3,1c008550 <memmove+0x86>
1c00853c:	0025c703          	lbu	a4,2(a1)
1c008540:	00350813          	addi	a6,a0,3
1c008544:	00358893          	addi	a7,a1,3
1c008548:	00e50123          	sb	a4,2(a0)
1c00854c:	ffd60313          	addi	t1,a2,-3
1c008550:	8e1d                	sub	a2,a2,a5
1c008552:	00265713          	srli	a4,a2,0x2
1c008556:	00f506b3          	add	a3,a0,a5
1c00855a:	95be                	add	a1,a1,a5
1c00855c:	1a070363          	beqz	a4,1c008702 <memmove+0x238>
1c008560:	004740fb          	lp.setup	x1,a4,1c008568 <memmove+0x9e>
1c008564:	0045a78b          	p.lw	a5,4(a1!)
1c008568:	00f6a22b          	p.sw	a5,4(a3!)
1c00856c:	c20635b3          	p.bclr	a1,a2,1,0
1c008570:	40b306b3          	sub	a3,t1,a1
1c008574:	00b807b3          	add	a5,a6,a1
1c008578:	00b88733          	add	a4,a7,a1
1c00857c:	14b60e63          	beq	a2,a1,1c0086d8 <memmove+0x20e>
1c008580:	00074603          	lbu	a2,0(a4)
1c008584:	00c78023          	sb	a2,0(a5)
1c008588:	1416a863          	p.beqimm	a3,1,1c0086d8 <memmove+0x20e>
1c00858c:	00174603          	lbu	a2,1(a4)
1c008590:	00c780a3          	sb	a2,1(a5)
1c008594:	1426a263          	p.beqimm	a3,2,1c0086d8 <memmove+0x20e>
1c008598:	00274603          	lbu	a2,2(a4)
1c00859c:	00c78123          	sb	a2,2(a5)
1c0085a0:	1236ac63          	p.beqimm	a3,3,1c0086d8 <memmove+0x20e>
1c0085a4:	00374603          	lbu	a2,3(a4)
1c0085a8:	00c781a3          	sb	a2,3(a5)
1c0085ac:	1246a663          	p.beqimm	a3,4,1c0086d8 <memmove+0x20e>
1c0085b0:	00474603          	lbu	a2,4(a4)
1c0085b4:	00c78223          	sb	a2,4(a5)
1c0085b8:	1256a063          	p.beqimm	a3,5,1c0086d8 <memmove+0x20e>
1c0085bc:	00574703          	lbu	a4,5(a4)
1c0085c0:	00e782a3          	sb	a4,5(a5)
1c0085c4:	8082                	ret
1c0085c6:	ffc60793          	addi	a5,a2,-4
1c0085ca:	00f50833          	add	a6,a0,a5
1c0085ce:	00f58333          	add	t1,a1,a5
1c0085d2:	00c58733          	add	a4,a1,a2
1c0085d6:	00c508b3          	add	a7,a0,a2
1c0085da:	05073733          	p.sletu	a4,a4,a6
1c0085de:	0468b833          	p.sletu	a6,a7,t1
1c0085e2:	86ba                	mv	a3,a4
1c0085e4:	8742                	mv	a4,a6
1c0085e6:	8f55                	or	a4,a4,a3
1c0085e8:	0ff77713          	andi	a4,a4,255
1c0085ec:	cb65                	beqz	a4,1c0086dc <memmove+0x212>
1c0085ee:	00863713          	sltiu	a4,a2,8
1c0085f2:	00174713          	xori	a4,a4,1
1c0085f6:	0ff77713          	andi	a4,a4,255
1c0085fa:	c36d                	beqz	a4,1c0086dc <memmove+0x212>
1c0085fc:	fa233733          	p.bclr	a4,t1,29,2
1c008600:	fff60893          	addi	a7,a2,-1
1c008604:	cb65                	beqz	a4,1c0086f4 <memmove+0x22a>
1c008606:	011586b3          	add	a3,a1,a7
1c00860a:	0006c683          	lbu	a3,0(a3)
1c00860e:	00d548a3          	p.sb	a3,a7(a0)
1c008612:	02172463          	p.beqimm	a4,1,1c00863a <memmove+0x170>
1c008616:	ffe60893          	addi	a7,a2,-2
1c00861a:	011586b3          	add	a3,a1,a7
1c00861e:	0006c683          	lbu	a3,0(a3)
1c008622:	00d548a3          	p.sb	a3,a7(a0)
1c008626:	00373a63          	p.bneimm	a4,3,1c00863a <memmove+0x170>
1c00862a:	ffd60893          	addi	a7,a2,-3
1c00862e:	011586b3          	add	a3,a1,a7
1c008632:	0006c683          	lbu	a3,0(a3)
1c008636:	00d548a3          	p.sb	a3,a7(a0)
1c00863a:	8e19                	sub	a2,a2,a4
1c00863c:	8f99                	sub	a5,a5,a4
1c00863e:	00265713          	srli	a4,a2,0x2
1c008642:	00f506b3          	add	a3,a0,a5
1c008646:	97ae                	add	a5,a5,a1
1c008648:	cb5d                	beqz	a4,1c0086fe <memmove+0x234>
1c00864a:	004740fb          	lp.setup	x1,a4,1c008652 <memmove+0x188>
1c00864e:	ffc7a80b          	p.lw	a6,-4(a5!)
1c008652:	ff06ae2b          	p.sw	a6,-4(a3!)
1c008656:	c20637b3          	p.bclr	a5,a2,1,0
1c00865a:	40f888b3          	sub	a7,a7,a5
1c00865e:	06f60d63          	beq	a2,a5,1c0086d8 <memmove+0x20e>
1c008662:	fff88793          	addi	a5,a7,-1
1c008666:	00f58733          	add	a4,a1,a5
1c00866a:	00074703          	lbu	a4,0(a4)
1c00866e:	00e547a3          	p.sb	a4,a5(a0)
1c008672:	c3bd                	beqz	a5,1c0086d8 <memmove+0x20e>
1c008674:	ffe88793          	addi	a5,a7,-2
1c008678:	00f58733          	add	a4,a1,a5
1c00867c:	00074703          	lbu	a4,0(a4)
1c008680:	00e547a3          	p.sb	a4,a5(a0)
1c008684:	cbb1                	beqz	a5,1c0086d8 <memmove+0x20e>
1c008686:	ffd88793          	addi	a5,a7,-3
1c00868a:	00f58733          	add	a4,a1,a5
1c00868e:	00074703          	lbu	a4,0(a4)
1c008692:	00e547a3          	p.sb	a4,a5(a0)
1c008696:	c3a9                	beqz	a5,1c0086d8 <memmove+0x20e>
1c008698:	ffc88793          	addi	a5,a7,-4
1c00869c:	00f58733          	add	a4,a1,a5
1c0086a0:	00074703          	lbu	a4,0(a4)
1c0086a4:	00e547a3          	p.sb	a4,a5(a0)
1c0086a8:	cb85                	beqz	a5,1c0086d8 <memmove+0x20e>
1c0086aa:	ffb88793          	addi	a5,a7,-5
1c0086ae:	00f58733          	add	a4,a1,a5
1c0086b2:	00074703          	lbu	a4,0(a4)
1c0086b6:	00e547a3          	p.sb	a4,a5(a0)
1c0086ba:	cf99                	beqz	a5,1c0086d8 <memmove+0x20e>
1c0086bc:	18e9                	addi	a7,a7,-6
1c0086be:	95c6                	add	a1,a1,a7
1c0086c0:	0005c783          	lbu	a5,0(a1)
1c0086c4:	00f548a3          	p.sb	a5,a7(a0)
1c0086c8:	8082                	ret
1c0086ca:	87aa                	mv	a5,a0
1c0086cc:	004640fb          	lp.setup	x1,a2,1c0086d4 <memmove+0x20a>
1c0086d0:	0015c70b          	p.lbu	a4,1(a1!)
1c0086d4:	00e780ab          	p.sb	a4,1(a5!)
1c0086d8:	8082                	ret
1c0086da:	8082                	ret
1c0086dc:	167d                	addi	a2,a2,-1
1c0086de:	00c507b3          	add	a5,a0,a2
1c0086e2:	95b2                	add	a1,a1,a2
1c0086e4:	0605                	addi	a2,a2,1
1c0086e6:	004640fb          	lp.setup	x1,a2,1c0086ee <memmove+0x224>
1c0086ea:	fff5c70b          	p.lbu	a4,-1(a1!)
1c0086ee:	fee78fab          	p.sb	a4,-1(a5!)
1c0086f2:	8082                	ret
1c0086f4:	88b2                	mv	a7,a2
1c0086f6:	b791                	j	1c00863a <memmove+0x170>
1c0086f8:	882a                	mv	a6,a0
1c0086fa:	8332                	mv	t1,a2
1c0086fc:	bd91                	j	1c008550 <memmove+0x86>
1c0086fe:	4705                	li	a4,1
1c008700:	b7a9                	j	1c00864a <memmove+0x180>
1c008702:	4705                	li	a4,1
1c008704:	bdb1                	j	1c008560 <memmove+0x96>

1c008706 <strchr>:
1c008706:	00054783          	lbu	a5,0(a0)
1c00870a:	0ff5f593          	andi	a1,a1,255
1c00870e:	00b78c63          	beq	a5,a1,1c008726 <strchr+0x20>
1c008712:	cb99                	beqz	a5,1c008728 <strchr+0x22>
1c008714:	00150793          	addi	a5,a0,1
1c008718:	a011                	j	1c00871c <strchr+0x16>
1c00871a:	c719                	beqz	a4,1c008728 <strchr+0x22>
1c00871c:	853e                	mv	a0,a5
1c00871e:	0017c70b          	p.lbu	a4,1(a5!)
1c008722:	feb71ce3          	bne	a4,a1,1c00871a <strchr+0x14>
1c008726:	8082                	ret
1c008728:	0015b593          	seqz	a1,a1
1c00872c:	40b005b3          	neg	a1,a1
1c008730:	8d6d                	and	a0,a0,a1
1c008732:	8082                	ret

1c008734 <pos_libc_fputc_locked>:
1c008734:	6689                	lui	a3,0x2
1c008736:	f14027f3          	csrr	a5,mhartid
1c00873a:	f8068693          	addi	a3,a3,-128 # 1f80 <__cluster_text_size+0x1f80>
1c00873e:	00379713          	slli	a4,a5,0x3
1c008742:	078a                	slli	a5,a5,0x2
1c008744:	8ff5                	and	a5,a5,a3
1c008746:	ee873733          	p.bclr	a4,a4,23,8
1c00874a:	1a10f6b7          	lui	a3,0x1a10f
1c00874e:	0ff57513          	andi	a0,a0,255
1c008752:	9736                	add	a4,a4,a3
1c008754:	00a7e723          	p.sw	a0,a4(a5)
1c008758:	4501                	li	a0,0
1c00875a:	8082                	ret

1c00875c <pos_libc_prf_locked>:
1c00875c:	a0a9                	j	1c0087a6 <pos_libc_prf>

1c00875e <exit>:
1c00875e:	1141                	addi	sp,sp,-16
1c008760:	c606                	sw	ra,12(sp)
1c008762:	1a1047b7          	lui	a5,0x1a104
1c008766:	c1f54533          	p.bset	a0,a0,0,31
1c00876a:	0aa7a023          	sw	a0,160(a5) # 1a1040a0 <__l2_shared_end+0xa104098>
1c00876e:	3ed5                	jal	1c008362 <pos_wait_forever>

1c008770 <pos_io_start>:
1c008770:	4501                	li	a0,0
1c008772:	8082                	ret

1c008774 <pos_io_stop>:
1c008774:	4501                	li	a0,0
1c008776:	8082                	ret

1c008778 <printf>:
1c008778:	7139                	addi	sp,sp,-64
1c00877a:	02410313          	addi	t1,sp,36
1c00877e:	d432                	sw	a2,40(sp)
1c008780:	862a                	mv	a2,a0
1c008782:	1c008537          	lui	a0,0x1c008
1c008786:	d22e                	sw	a1,36(sp)
1c008788:	d636                	sw	a3,44(sp)
1c00878a:	4589                	li	a1,2
1c00878c:	869a                	mv	a3,t1
1c00878e:	73450513          	addi	a0,a0,1844 # 1c008734 <pos_libc_fputc_locked>
1c008792:	ce06                	sw	ra,28(sp)
1c008794:	d83a                	sw	a4,48(sp)
1c008796:	da3e                	sw	a5,52(sp)
1c008798:	dc42                	sw	a6,56(sp)
1c00879a:	de46                	sw	a7,60(sp)
1c00879c:	c61a                	sw	t1,12(sp)
1c00879e:	3f7d                	jal	1c00875c <pos_libc_prf_locked>
1c0087a0:	40f2                	lw	ra,28(sp)
1c0087a2:	6121                	addi	sp,sp,64
1c0087a4:	8082                	ret

1c0087a6 <pos_libc_prf>:
1c0087a6:	7169                	addi	sp,sp,-304
1c0087a8:	12812423          	sw	s0,296(sp)
1c0087ac:	4401                	li	s0,0
1c0087ae:	11612823          	sw	s6,272(sp)
1c0087b2:	11712623          	sw	s7,268(sp)
1c0087b6:	11812423          	sw	s8,264(sp)
1c0087ba:	11912223          	sw	s9,260(sp)
1c0087be:	11a12023          	sw	s10,256(sp)
1c0087c2:	dfee                	sw	s11,252(sp)
1c0087c4:	12112623          	sw	ra,300(sp)
1c0087c8:	8da2                	mv	s11,s0
1c0087ca:	12912223          	sw	s1,292(sp)
1c0087ce:	13212023          	sw	s2,288(sp)
1c0087d2:	11312e23          	sw	s3,284(sp)
1c0087d6:	11412c23          	sw	s4,280(sp)
1c0087da:	11512a23          	sw	s5,276(sp)
1c0087de:	8b2a                	mv	s6,a0
1c0087e0:	8d2e                	mv	s10,a1
1c0087e2:	8c36                	mv	s8,a3
1c0087e4:	1c000bb7          	lui	s7,0x1c000
1c0087e8:	02410c93          	addi	s9,sp,36
1c0087ec:	8432                	mv	s0,a2
1c0087ee:	00044503          	lbu	a0,0(s0)
1c0087f2:	0405                	addi	s0,s0,1
1c0087f4:	cd11                	beqz	a0,1c008810 <pos_libc_prf+0x6a>
1c0087f6:	02500793          	li	a5,37
1c0087fa:	04f50863          	beq	a0,a5,1c00884a <pos_libc_prf+0xa4>
1c0087fe:	85ea                	mv	a1,s10
1c008800:	9b02                	jalr	s6
1c008802:	31f52563          	p.beqimm	a0,-1,1c008b0c <pos_libc_prf+0x366>
1c008806:	0d85                	addi	s11,s11,1
1c008808:	00044503          	lbu	a0,0(s0)
1c00880c:	0405                	addi	s0,s0,1
1c00880e:	f565                	bnez	a0,1c0087f6 <pos_libc_prf+0x50>
1c008810:	846e                	mv	s0,s11
1c008812:	8522                	mv	a0,s0
1c008814:	12c12083          	lw	ra,300(sp)
1c008818:	12812403          	lw	s0,296(sp)
1c00881c:	12412483          	lw	s1,292(sp)
1c008820:	12012903          	lw	s2,288(sp)
1c008824:	11c12983          	lw	s3,284(sp)
1c008828:	11812a03          	lw	s4,280(sp)
1c00882c:	11412a83          	lw	s5,276(sp)
1c008830:	11012b03          	lw	s6,272(sp)
1c008834:	10c12b83          	lw	s7,268(sp)
1c008838:	10812c03          	lw	s8,264(sp)
1c00883c:	10412c83          	lw	s9,260(sp)
1c008840:	10012d03          	lw	s10,256(sp)
1c008844:	5dfe                	lw	s11,252(sp)
1c008846:	6155                	addi	sp,sp,304
1c008848:	8082                	ret
1c00884a:	00044483          	lbu	s1,0(s0)
1c00884e:	02000693          	li	a3,32
1c008852:	00140a93          	addi	s5,s0,1
1c008856:	054b8513          	addi	a0,s7,84 # 1c000054 <__DTOR_END__+0x38>
1c00885a:	85a6                	mv	a1,s1
1c00885c:	c836                	sw	a3,16(sp)
1c00885e:	cc02                	sw	zero,24(sp)
1c008860:	ca02                	sw	zero,20(sp)
1c008862:	ce02                	sw	zero,28(sp)
1c008864:	c602                	sw	zero,12(sp)
1c008866:	02300913          	li	s2,35
1c00886a:	02d00a13          	li	s4,45
1c00886e:	89d6                	mv	s3,s5
1c008870:	3d59                	jal	1c008706 <strchr>
1c008872:	c915                	beqz	a0,1c0088a6 <pos_libc_prf+0x100>
1c008874:	2b248b63          	beq	s1,s2,1c008b2a <pos_libc_prf+0x384>
1c008878:	0c997463          	bleu	s1,s2,1c008940 <pos_libc_prf+0x19a>
1c00887c:	2b448363          	beq	s1,s4,1c008b22 <pos_libc_prf+0x37c>
1c008880:	03000613          	li	a2,48
1c008884:	28c48a63          	beq	s1,a2,1c008b18 <pos_libc_prf+0x372>
1c008888:	02b00693          	li	a3,43
1c00888c:	28d48263          	beq	s1,a3,1c008b10 <pos_libc_prf+0x36a>
1c008890:	8456                	mv	s0,s5
1c008892:	00044483          	lbu	s1,0(s0)
1c008896:	00140a93          	addi	s5,s0,1
1c00889a:	054b8513          	addi	a0,s7,84
1c00889e:	85a6                	mv	a1,s1
1c0088a0:	89d6                	mv	s3,s5
1c0088a2:	3595                	jal	1c008706 <strchr>
1c0088a4:	f961                	bnez	a0,1c008874 <pos_libc_prf+0xce>
1c0088a6:	02a00613          	li	a2,42
1c0088aa:	2ac48663          	beq	s1,a2,1c008b56 <pos_libc_prf+0x3b0>
1c0088ae:	fd048613          	addi	a2,s1,-48
1c0088b2:	45a5                	li	a1,9
1c0088b4:	4901                	li	s2,0
1c0088b6:	28c5f063          	bleu	a2,a1,1c008b36 <pos_libc_prf+0x390>
1c0088ba:	02e00693          	li	a3,46
1c0088be:	5a7d                	li	s4,-1
1c0088c0:	2ed48363          	beq	s1,a3,1c008ba6 <pos_libc_prf+0x400>
1c0088c4:	1c0007b7          	lui	a5,0x1c000
1c0088c8:	85a6                	mv	a1,s1
1c0088ca:	05c78513          	addi	a0,a5,92 # 1c00005c <__DTOR_END__+0x40>
1c0088ce:	3d25                	jal	1c008706 <strchr>
1c0088d0:	844e                	mv	s0,s3
1c0088d2:	c509                	beqz	a0,1c0088dc <pos_libc_prf+0x136>
1c0088d4:	0009c483          	lbu	s1,0(s3)
1c0088d8:	00198413          	addi	s0,s3,1
1c0088dc:	06700693          	li	a3,103
1c0088e0:	2896d963          	ble	s1,a3,1c008b72 <pos_libc_prf+0x3cc>
1c0088e4:	07000693          	li	a3,112
1c0088e8:	7cd48b63          	beq	s1,a3,1c0090be <pos_libc_prf+0x918>
1c0088ec:	2e96d163          	ble	s1,a3,1c008bce <pos_libc_prf+0x428>
1c0088f0:	07500693          	li	a3,117
1c0088f4:	12d489e3          	beq	s1,a3,1c009226 <pos_libc_prf+0xa80>
1c0088f8:	07800693          	li	a3,120
1c0088fc:	06d48663          	beq	s1,a3,1c008968 <pos_libc_prf+0x1c2>
1c008900:	07300693          	li	a3,115
1c008904:	18d49fe3          	bne	s1,a3,1c0092a2 <pos_libc_prf+0xafc>
1c008908:	000c2583          	lw	a1,0(s8)
1c00890c:	004c0993          	addi	s3,s8,4
1c008910:	4481                	li	s1,0
1c008912:	86ae                	mv	a3,a1
1c008914:	0c8350fb          	lp.setupi	x1,200,1c008920 <pos_libc_prf+0x17a>
1c008918:	0016c70b          	p.lbu	a4,1(a3!) # 1a10f001 <__l2_shared_end+0xa10eff9>
1c00891c:	18070ae3          	beqz	a4,1c0092b0 <pos_libc_prf+0xb0a>
1c008920:	0485                	addi	s1,s1,1
1c008922:	000a4763          	bltz	s4,1c008930 <pos_libc_prf+0x18a>
1c008926:	0544c4b3          	p.min	s1,s1,s4
1c00892a:	8c4e                	mv	s8,s3
1c00892c:	ec0481e3          	beqz	s1,1c0087ee <pos_libc_prf+0x48>
1c008930:	8626                	mv	a2,s1
1c008932:	8566                	mv	a0,s9
1c008934:	3cb9                	jal	1c008392 <memcpy>
1c008936:	8c4e                	mv	s8,s3
1c008938:	1b24db63          	ble	s2,s1,1c008aee <pos_libc_prf+0x348>
1c00893c:	c602                	sw	zero,12(sp)
1c00893e:	a0f9                	j	1c008a0c <pos_libc_prf+0x266>
1c008940:	ec0488e3          	beqz	s1,1c008810 <pos_libc_prf+0x6a>
1c008944:	02000593          	li	a1,32
1c008948:	f4b494e3          	bne	s1,a1,1c008890 <pos_libc_prf+0xea>
1c00894c:	4785                	li	a5,1
1c00894e:	cc3e                	sw	a5,24(sp)
1c008950:	8456                	mv	s0,s5
1c008952:	b781                	j	1c008892 <pos_libc_prf+0xec>
1c008954:	06300693          	li	a3,99
1c008958:	0ad48de3          	beq	s1,a3,1c009212 <pos_libc_prf+0xa6c>
1c00895c:	0096cde3          	blt	a3,s1,1c009176 <pos_libc_prf+0x9d0>
1c008960:	05800693          	li	a3,88
1c008964:	12d49fe3          	bne	s1,a3,1c0092a2 <pos_libc_prf+0xafc>
1c008968:	47b2                	lw	a5,12(sp)
1c00896a:	004c0893          	addi	a7,s8,4
1c00896e:	000c2503          	lw	a0,0(s8)
1c008972:	260788e3          	beqz	a5,1c0093e2 <pos_libc_prf+0xc3c>
1c008976:	76e1                	lui	a3,0xffff8
1c008978:	8306c693          	xori	a3,a3,-2000
1c00897c:	02d11223          	sh	a3,36(sp)
1c008980:	4309                	li	t1,2
1c008982:	02610613          	addi	a2,sp,38
1c008986:	86b2                	mv	a3,a2
1c008988:	4ea5                	li	t4,9
1c00898a:	f6453733          	p.bclr	a4,a0,27,4
1c00898e:	0ff77793          	andi	a5,a4,255
1c008992:	03078593          	addi	a1,a5,48
1c008996:	8111                	srli	a0,a0,0x4
1c008998:	05778793          	addi	a5,a5,87
1c00899c:	70eee963          	bltu	t4,a4,1c0090ae <pos_libc_prf+0x908>
1c0089a0:	00b680ab          	p.sb	a1,1(a3!) # ffff8001 <pulp__FC+0xffff8002>
1c0089a4:	f17d                	bnez	a0,1c00898a <pos_libc_prf+0x1e4>
1c0089a6:	40c68733          	sub	a4,a3,a2
1c0089aa:	01475d63          	ble	s4,a4,1c0089c4 <pos_libc_prf+0x21e>
1c0089ae:	40d605b3          	sub	a1,a2,a3
1c0089b2:	03000513          	li	a0,48
1c0089b6:	95d2                	add	a1,a1,s4
1c0089b8:	0045c0fb          	lp.setup	x1,a1,1c0089c0 <pos_libc_prf+0x21a>
1c0089bc:	00a680ab          	p.sb	a0,1(a3!)
1c0089c0:	40c68733          	sub	a4,a3,a2
1c0089c4:	fe068fab          	p.sb	zero,-1(a3!)
1c0089c8:	00d67c63          	bleu	a3,a2,1c0089e0 <pos_libc_prf+0x23a>
1c0089cc:	00064583          	lbu	a1,0(a2)
1c0089d0:	0006c783          	lbu	a5,0(a3)
1c0089d4:	feb68fab          	p.sb	a1,-1(a3!)
1c0089d8:	00f600ab          	p.sb	a5,1(a2!)
1c0089dc:	fed668e3          	bltu	a2,a3,1c0089cc <pos_libc_prf+0x226>
1c0089e0:	05800693          	li	a3,88
1c0089e4:	20d483e3          	beq	s1,a3,1c0093ea <pos_libc_prf+0xc44>
1c0089e8:	46b2                	lw	a3,12(sp)
1c0089ea:	006704b3          	add	s1,a4,t1
1c0089ee:	c299                	beqz	a3,1c0089f4 <pos_libc_prf+0x24e>
1c0089f0:	4709                	li	a4,2
1c0089f2:	c63a                	sw	a4,12(sp)
1c0089f4:	0c800793          	li	a5,200
1c0089f8:	23fa24e3          	p.beqimm	s4,-1,1c009420 <pos_libc_prf+0xc7a>
1c0089fc:	1097c863          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c008a00:	02000793          	li	a5,32
1c008a04:	8c46                	mv	s8,a7
1c008a06:	c83e                	sw	a5,16(sp)
1c008a08:	0f24d163          	ble	s2,s1,1c008aea <pos_libc_prf+0x344>
1c008a0c:	4772                	lw	a4,28(sp)
1c008a0e:	0c0702e3          	beqz	a4,1c0092d2 <pos_libc_prf+0xb2c>
1c008a12:	009c87b3          	add	a5,s9,s1
1c008a16:	40f007b3          	neg	a5,a5
1c008a1a:	fa27b7b3          	p.bclr	a5,a5,29,2
1c008a1e:	4595                	li	a1,5
1c008a20:	00378613          	addi	a2,a5,3
1c008a24:	fff90693          	addi	a3,s2,-1
1c008a28:	04b67633          	p.maxu	a2,a2,a1
1c008a2c:	8e85                	sub	a3,a3,s1
1c008a2e:	409905b3          	sub	a1,s2,s1
1c008a32:	06c6e163          	bltu	a3,a2,1c008a94 <pos_libc_prf+0x2ee>
1c008a36:	8626                	mv	a2,s1
1c008a38:	cb85                	beqz	a5,1c008a68 <pos_libc_prf+0x2c2>
1c008a3a:	1998                	addi	a4,sp,240
1c008a3c:	00970633          	add	a2,a4,s1
1c008a40:	02000693          	li	a3,32
1c008a44:	f2d60a23          	sb	a3,-204(a2)
1c008a48:	00148613          	addi	a2,s1,1
1c008a4c:	0017ae63          	p.beqimm	a5,1,1c008a68 <pos_libc_prf+0x2c2>
1c008a50:	963a                	add	a2,a2,a4
1c008a52:	f2d60a23          	sb	a3,-204(a2)
1c008a56:	00248613          	addi	a2,s1,2
1c008a5a:	0037b763          	p.bneimm	a5,3,1c008a68 <pos_libc_prf+0x2c2>
1c008a5e:	963a                	add	a2,a2,a4
1c008a60:	f2d60a23          	sb	a3,-204(a2)
1c008a64:	00348613          	addi	a2,s1,3
1c008a68:	8d9d                	sub	a1,a1,a5
1c008a6a:	0025d693          	srli	a3,a1,0x2
1c008a6e:	97a6                	add	a5,a5,s1
1c008a70:	97e6                	add	a5,a5,s9
1c008a72:	42068fe3          	beqz	a3,1c0096b0 <pos_libc_prf+0xf0a>
1c008a76:	0076c0fb          	lp.setup	x1,a3,1c008a84 <pos_libc_prf+0x2de>
1c008a7a:	1c000737          	lui	a4,0x1c000
1c008a7e:	05070713          	addi	a4,a4,80 # 1c000050 <__DTOR_END__+0x34>
1c008a82:	4318                	lw	a4,0(a4)
1c008a84:	00e7a22b          	p.sw	a4,4(a5!)
1c008a88:	c205b7b3          	p.bclr	a5,a1,1,0
1c008a8c:	00c784b3          	add	s1,a5,a2
1c008a90:	04b78c63          	beq	a5,a1,1c008ae8 <pos_libc_prf+0x342>
1c008a94:	198c                	addi	a1,sp,240
1c008a96:	009586b3          	add	a3,a1,s1
1c008a9a:	02000793          	li	a5,32
1c008a9e:	f2f68a23          	sb	a5,-204(a3)
1c008aa2:	00148693          	addi	a3,s1,1
1c008aa6:	0526d163          	ble	s2,a3,1c008ae8 <pos_libc_prf+0x342>
1c008aaa:	96ae                	add	a3,a3,a1
1c008aac:	f2f68a23          	sb	a5,-204(a3)
1c008ab0:	00248693          	addi	a3,s1,2
1c008ab4:	0326da63          	ble	s2,a3,1c008ae8 <pos_libc_prf+0x342>
1c008ab8:	96ae                	add	a3,a3,a1
1c008aba:	f2f68a23          	sb	a5,-204(a3)
1c008abe:	00348693          	addi	a3,s1,3
1c008ac2:	0326d363          	ble	s2,a3,1c008ae8 <pos_libc_prf+0x342>
1c008ac6:	96ae                	add	a3,a3,a1
1c008ac8:	f2f68a23          	sb	a5,-204(a3)
1c008acc:	00448693          	addi	a3,s1,4
1c008ad0:	0126dc63          	ble	s2,a3,1c008ae8 <pos_libc_prf+0x342>
1c008ad4:	96ae                	add	a3,a3,a1
1c008ad6:	f2f68a23          	sb	a5,-204(a3)
1c008ada:	00548713          	addi	a4,s1,5
1c008ade:	01275563          	ble	s2,a4,1c008ae8 <pos_libc_prf+0x342>
1c008ae2:	972e                	add	a4,a4,a1
1c008ae4:	f2f70a23          	sb	a5,-204(a4)
1c008ae8:	84ca                	mv	s1,s2
1c008aea:	d00482e3          	beqz	s1,1c0087ee <pos_libc_prf+0x48>
1c008aee:	8966                	mv	s2,s9
1c008af0:	419d8db3          	sub	s11,s11,s9
1c008af4:	a029                	j	1c008afe <pos_libc_prf+0x358>
1c008af6:	012d8733          	add	a4,s11,s2
1c008afa:	5a048f63          	beqz	s1,1c0090b8 <pos_libc_prf+0x912>
1c008afe:	0019450b          	p.lbu	a0,1(s2!)
1c008b02:	85ea                	mv	a1,s10
1c008b04:	14fd                	addi	s1,s1,-1
1c008b06:	9b02                	jalr	s6
1c008b08:	fff537e3          	p.bneimm	a0,-1,1c008af6 <pos_libc_prf+0x350>
1c008b0c:	547d                	li	s0,-1
1c008b0e:	b311                	j	1c008812 <pos_libc_prf+0x6c>
1c008b10:	4705                	li	a4,1
1c008b12:	ca3a                	sw	a4,20(sp)
1c008b14:	8456                	mv	s0,s5
1c008b16:	bbb5                	j	1c008892 <pos_libc_prf+0xec>
1c008b18:	03000713          	li	a4,48
1c008b1c:	c83a                	sw	a4,16(sp)
1c008b1e:	8456                	mv	s0,s5
1c008b20:	bb8d                	j	1c008892 <pos_libc_prf+0xec>
1c008b22:	4785                	li	a5,1
1c008b24:	ce3e                	sw	a5,28(sp)
1c008b26:	8456                	mv	s0,s5
1c008b28:	b3ad                	j	1c008892 <pos_libc_prf+0xec>
1c008b2a:	4685                	li	a3,1
1c008b2c:	c636                	sw	a3,12(sp)
1c008b2e:	8456                	mv	s0,s5
1c008b30:	b38d                	j	1c008892 <pos_libc_prf+0xec>
1c008b32:	8456                	mv	s0,s5
1c008b34:	0a85                	addi	s5,s5,1
1c008b36:	00291793          	slli	a5,s2,0x2
1c008b3a:	97ca                	add	a5,a5,s2
1c008b3c:	0786                	slli	a5,a5,0x1
1c008b3e:	97a6                	add	a5,a5,s1
1c008b40:	000ac483          	lbu	s1,0(s5)
1c008b44:	fd078913          	addi	s2,a5,-48
1c008b48:	fd048793          	addi	a5,s1,-48
1c008b4c:	fef5f3e3          	bleu	a5,a1,1c008b32 <pos_libc_prf+0x38c>
1c008b50:	00240993          	addi	s3,s0,2
1c008b54:	a811                	j	1c008b68 <pos_libc_prf+0x3c2>
1c008b56:	000c2903          	lw	s2,0(s8)
1c008b5a:	0c11                	addi	s8,s8,4
1c008b5c:	12094d63          	bltz	s2,1c008c96 <pos_libc_prf+0x4f0>
1c008b60:	000ac483          	lbu	s1,0(s5)
1c008b64:	00240993          	addi	s3,s0,2
1c008b68:	0c800693          	li	a3,200
1c008b6c:	04d95933          	p.minu	s2,s2,a3
1c008b70:	b3a9                	j	1c0088ba <pos_libc_prf+0x114>
1c008b72:	06500693          	li	a3,101
1c008b76:	12d4d563          	ble	a3,s1,1c008ca0 <pos_libc_prf+0x4fa>
1c008b7a:	04700693          	li	a3,71
1c008b7e:	dc96cbe3          	blt	a3,s1,1c008954 <pos_libc_prf+0x1ae>
1c008b82:	04500693          	li	a3,69
1c008b86:	10d4dd63          	ble	a3,s1,1c008ca0 <pos_libc_prf+0x4fa>
1c008b8a:	c80483e3          	beqz	s1,1c008810 <pos_libc_prf+0x6a>
1c008b8e:	02500693          	li	a3,37
1c008b92:	70d49863          	bne	s1,a3,1c0092a2 <pos_libc_prf+0xafc>
1c008b96:	85ea                	mv	a1,s10
1c008b98:	02500513          	li	a0,37
1c008b9c:	9b02                	jalr	s6
1c008b9e:	f7f527e3          	p.beqimm	a0,-1,1c008b0c <pos_libc_prf+0x366>
1c008ba2:	0d85                	addi	s11,s11,1
1c008ba4:	b195                	j	1c008808 <pos_libc_prf+0x62>
1c008ba6:	0009c783          	lbu	a5,0(s3)
1c008baa:	02a00693          	li	a3,42
1c008bae:	00198513          	addi	a0,s3,1
1c008bb2:	0ad79963          	bne	a5,a3,1c008c64 <pos_libc_prf+0x4be>
1c008bb6:	000c2a03          	lw	s4,0(s8)
1c008bba:	0019c483          	lbu	s1,1(s3)
1c008bbe:	0c11                	addi	s8,s8,4
1c008bc0:	0989                	addi	s3,s3,2
1c008bc2:	0c800693          	li	a3,200
1c008bc6:	cf46dfe3          	ble	s4,a3,1c0088c4 <pos_libc_prf+0x11e>
1c008bca:	5a7d                	li	s4,-1
1c008bcc:	b9e5                	j	1c0088c4 <pos_libc_prf+0x11e>
1c008bce:	06e00693          	li	a3,110
1c008bd2:	58d48763          	beq	s1,a3,1c009160 <pos_libc_prf+0x9ba>
1c008bd6:	5896dc63          	ble	s1,a3,1c00916e <pos_libc_prf+0x9c8>
1c008bda:	47b2                	lw	a5,12(sp)
1c008bdc:	004c0813          	addi	a6,s8,4
1c008be0:	000c2603          	lw	a2,0(s8)
1c008be4:	04078ee3          	beqz	a5,1c009440 <pos_libc_prf+0xc9a>
1c008be8:	03000793          	li	a5,48
1c008bec:	02f10223          	sb	a5,36(sp)
1c008bf0:	02060de3          	beqz	a2,1c00942a <pos_libc_prf+0xc84>
1c008bf4:	02510513          	addi	a0,sp,37
1c008bf8:	86aa                	mv	a3,a0
1c008bfa:	87b6                	mv	a5,a3
1c008bfc:	f8363733          	p.bclr	a4,a2,28,3
1c008c00:	03070713          	addi	a4,a4,48
1c008c04:	820d                	srli	a2,a2,0x3
1c008c06:	00e780ab          	p.sb	a4,1(a5!)
1c008c0a:	fa6d                	bnez	a2,1c008bfc <pos_libc_prf+0x456>
1c008c0c:	40a78733          	sub	a4,a5,a0
1c008c10:	01475d63          	ble	s4,a4,1c008c2a <pos_libc_prf+0x484>
1c008c14:	40fa0633          	sub	a2,s4,a5
1c008c18:	03000593          	li	a1,48
1c008c1c:	962a                	add	a2,a2,a0
1c008c1e:	004640fb          	lp.setup	x1,a2,1c008c26 <pos_libc_prf+0x480>
1c008c22:	00b780ab          	p.sb	a1,1(a5!)
1c008c26:	40a78733          	sub	a4,a5,a0
1c008c2a:	fe078fab          	p.sb	zero,-1(a5!)
1c008c2e:	00f6fc63          	bleu	a5,a3,1c008c46 <pos_libc_prf+0x4a0>
1c008c32:	0006c583          	lbu	a1,0(a3)
1c008c36:	0007c603          	lbu	a2,0(a5)
1c008c3a:	feb78fab          	p.sb	a1,-1(a5!)
1c008c3e:	00c680ab          	p.sb	a2,1(a3!)
1c008c42:	fef6e8e3          	bltu	a3,a5,1c008c32 <pos_libc_prf+0x48c>
1c008c46:	46b2                	lw	a3,12(sp)
1c008c48:	0c800793          	li	a5,200
1c008c4c:	00d704b3          	add	s1,a4,a3
1c008c50:	0bfa2de3          	p.beqimm	s4,-1,1c00950a <pos_libc_prf+0xd64>
1c008c54:	ea97cce3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c008c58:	02000793          	li	a5,32
1c008c5c:	8c42                	mv	s8,a6
1c008c5e:	c602                	sw	zero,12(sp)
1c008c60:	c83e                	sw	a5,16(sp)
1c008c62:	b35d                	j	1c008a08 <pos_libc_prf+0x262>
1c008c64:	fd078813          	addi	a6,a5,-48
1c008c68:	46a5                	li	a3,9
1c008c6a:	84be                	mv	s1,a5
1c008c6c:	862a                	mv	a2,a0
1c008c6e:	4a01                	li	s4,0
1c008c70:	45a5                	li	a1,9
1c008c72:	89aa                	mv	s3,a0
1c008c74:	c506e8e3          	bltu	a3,a6,1c0088c4 <pos_libc_prf+0x11e>
1c008c78:	002a1793          	slli	a5,s4,0x2
1c008c7c:	97d2                	add	a5,a5,s4
1c008c7e:	0786                	slli	a5,a5,0x1
1c008c80:	97a6                	add	a5,a5,s1
1c008c82:	0016448b          	p.lbu	s1,1(a2!)
1c008c86:	fd078a13          	addi	s4,a5,-48
1c008c8a:	fd048793          	addi	a5,s1,-48
1c008c8e:	fef5f5e3          	bleu	a5,a1,1c008c78 <pos_libc_prf+0x4d2>
1c008c92:	89b2                	mv	s3,a2
1c008c94:	b73d                	j	1c008bc2 <pos_libc_prf+0x41c>
1c008c96:	4705                	li	a4,1
1c008c98:	41200933          	neg	s2,s2
1c008c9c:	ce3a                	sw	a4,28(sp)
1c008c9e:	b5c9                	j	1c008b60 <pos_libc_prf+0x3ba>
1c008ca0:	0c1d                	addi	s8,s8,7
1c008ca2:	c40c3c33          	p.bclr	s8,s8,2,0
1c008ca6:	000c2683          	lw	a3,0(s8)
1c008caa:	004c2803          	lw	a6,4(s8)
1c008cae:	7ff00613          	li	a2,2047
1c008cb2:	0156d893          	srli	a7,a3,0x15
1c008cb6:	01485513          	srli	a0,a6,0x14
1c008cba:	00b81593          	slli	a1,a6,0xb
1c008cbe:	00b8e5b3          	or	a1,a7,a1
1c008cc2:	e8b53533          	p.bclr	a0,a0,20,11
1c008cc6:	0c21                	addi	s8,s8,8
1c008cc8:	06ae                	slli	a3,a3,0xb
1c008cca:	c1f5b5b3          	p.bclr	a1,a1,0,31
1c008cce:	7ac50b63          	beq	a0,a2,1c009484 <pos_libc_prf+0xcde>
1c008cd2:	04600613          	li	a2,70
1c008cd6:	00c49463          	bne	s1,a2,1c008cde <pos_libc_prf+0x538>
1c008cda:	06600493          	li	s1,102
1c008cde:	00d56633          	or	a2,a0,a3
1c008ce2:	8e4d                	or	a2,a2,a1
1c008ce4:	7c060b63          	beqz	a2,1c0094ba <pos_libc_prf+0xd14>
1c008ce8:	c0250513          	addi	a0,a0,-1022
1c008cec:	c1f5c333          	p.bset	t1,a1,0,31
1c008cf0:	140842e3          	bltz	a6,1c009634 <pos_libc_prf+0xe8e>
1c008cf4:	4752                	lw	a4,20(sp)
1c008cf6:	180703e3          	beqz	a4,1c00967c <pos_libc_prf+0xed6>
1c008cfa:	02b00613          	li	a2,43
1c008cfe:	02c10223          	sb	a2,36(sp)
1c008d02:	02510893          	addi	a7,sp,37
1c008d06:	5679                	li	a2,-2
1c008d08:	4801                	li	a6,0
1c008d0a:	06c55763          	ble	a2,a0,1c008d78 <pos_libc_prf+0x5d2>
1c008d0e:	33333e37          	lui	t3,0x33333
1c008d12:	80000eb7          	lui	t4,0x80000
1c008d16:	332e0e13          	addi	t3,t3,818 # 33333332 <__cluster_text_end+0x17323332>
1c008d1a:	fffece93          	not	t4,t4
1c008d1e:	5f79                	li	t5,-2
1c008d20:	a011                	j	1c008d24 <pos_libc_prf+0x57e>
1c008d22:	853e                	mv	a0,a5
1c008d24:	01f31613          	slli	a2,t1,0x1f
1c008d28:	0016d713          	srli	a4,a3,0x1
1c008d2c:	fc16b7b3          	p.bclr	a5,a3,30,1
1c008d30:	8f51                	or	a4,a4,a2
1c008d32:	00e786b3          	add	a3,a5,a4
1c008d36:	00f6b7b3          	sltu	a5,a3,a5
1c008d3a:	00135313          	srli	t1,t1,0x1
1c008d3e:	933e                	add	t1,t1,a5
1c008d40:	00150793          	addi	a5,a0,1
1c008d44:	fc6e6fe3          	bltu	t3,t1,1c008d22 <pos_libc_prf+0x57c>
1c008d48:	00269613          	slli	a2,a3,0x2
1c008d4c:	01e6d593          	srli	a1,a3,0x1e
1c008d50:	00231713          	slli	a4,t1,0x2
1c008d54:	96b2                	add	a3,a3,a2
1c008d56:	8f4d                	or	a4,a4,a1
1c008d58:	933a                	add	t1,t1,a4
1c008d5a:	00c6b633          	sltu	a2,a3,a2
1c008d5e:	9332                	add	t1,t1,a2
1c008d60:	01f6d713          	srli	a4,a3,0x1f
1c008d64:	0509                	addi	a0,a0,2
1c008d66:	187d                	addi	a6,a6,-1
1c008d68:	01d31663          	bne	t1,t4,1c008d74 <pos_libc_prf+0x5ce>
1c008d6c:	0686                	slli	a3,a3,0x1
1c008d6e:	fc174333          	p.bset	t1,a4,30,1
1c008d72:	853e                	mv	a0,a5
1c008d74:	fbe548e3          	blt	a0,t5,1c008d24 <pos_libc_prf+0x57e>
1c008d78:	06a05763          	blez	a0,1c008de6 <pos_libc_prf+0x640>
1c008d7c:	80000eb7          	lui	t4,0x80000
1c008d80:	4f15                	li	t5,5
1c008d82:	fffece93          	not	t4,t4
1c008d86:	00268613          	addi	a2,a3,2
1c008d8a:	00d636b3          	sltu	a3,a2,a3
1c008d8e:	9336                	add	t1,t1,a3
1c008d90:	03e357b3          	divu	a5,t1,t5
1c008d94:	00365593          	srli	a1,a2,0x3
1c008d98:	157d                	addi	a0,a0,-1
1c008d9a:	0805                	addi	a6,a6,1
1c008d9c:	00279713          	slli	a4,a5,0x2
1c008da0:	973e                	add	a4,a4,a5
1c008da2:	40e30333          	sub	t1,t1,a4
1c008da6:	01d31713          	slli	a4,t1,0x1d
1c008daa:	8dd9                	or	a1,a1,a4
1c008dac:	03e5d5b3          	divu	a1,a1,t5
1c008db0:	00359693          	slli	a3,a1,0x3
1c008db4:	00559713          	slli	a4,a1,0x5
1c008db8:	9736                	add	a4,a4,a3
1c008dba:	40e60733          	sub	a4,a2,a4
1c008dbe:	03e75733          	divu	a4,a4,t5
1c008dc2:	81f5                	srli	a1,a1,0x1d
1c008dc4:	97ae                	add	a5,a5,a1
1c008dc6:	96ba                	add	a3,a3,a4
1c008dc8:	00e6b733          	sltu	a4,a3,a4
1c008dcc:	00f70333          	add	t1,a4,a5
1c008dd0:	01f6d793          	srli	a5,a3,0x1f
1c008dd4:	0306                	slli	t1,t1,0x1
1c008dd6:	0067e333          	or	t1,a5,t1
1c008dda:	0686                	slli	a3,a3,0x1
1c008ddc:	157d                	addi	a0,a0,-1
1c008dde:	fe6ef9e3          	bleu	t1,t4,1c008dd0 <pos_libc_prf+0x62a>
1c008de2:	faa042e3          	bgtz	a0,1c008d86 <pos_libc_prf+0x5e0>
1c008de6:	4611                	li	a2,4
1c008de8:	8e09                	sub	a2,a2,a0
1c008dea:	012640fb          	lp.setup	x1,a2,1c008e0e <pos_libc_prf+0x668>
1c008dee:	01f31713          	slli	a4,t1,0x1f
1c008df2:	0016d793          	srli	a5,a3,0x1
1c008df6:	8fd9                	or	a5,a5,a4
1c008df8:	fc16b6b3          	p.bclr	a3,a3,30,1
1c008dfc:	00f68eb3          	add	t4,a3,a5
1c008e00:	00135313          	srli	t1,t1,0x1
1c008e04:	00deb6b3          	sltu	a3,t4,a3
1c008e08:	00668533          	add	a0,a3,t1
1c008e0c:	832a                	mv	t1,a0
1c008e0e:	86f6                	mv	a3,t4
1c008e10:	06700693          	li	a3,103
1c008e14:	6c0a4e63          	bltz	s4,1c0094f0 <pos_libc_prf+0xd4a>
1c008e18:	62d48863          	beq	s1,a3,1c009448 <pos_libc_prf+0xca2>
1c008e1c:	04700693          	li	a3,71
1c008e20:	62d48463          	beq	s1,a3,1c009448 <pos_libc_prf+0xca2>
1c008e24:	06600693          	li	a3,102
1c008e28:	78d48963          	beq	s1,a3,1c0095ba <pos_libc_prf+0xe14>
1c008e2c:	001a0f13          	addi	t5,s4,1
1c008e30:	45c1                	li	a1,16
1c008e32:	04bf4f33          	p.min	t5,t5,a1
1c008e36:	1f7d                	addi	t5,t5,-1
1c008e38:	4e01                	li	t3,0
1c008e3a:	4581                	li	a1,0
1c008e3c:	080006b7          	lui	a3,0x8000
1c008e40:	4f95                	li	t6,5
1c008e42:	0f05                	addi	t5,t5,1
1c008e44:	02ff40fb          	lp.setup	x1,t5,1c008ea2 <pos_libc_prf+0x6fc>
1c008e48:	00258713          	addi	a4,a1,2
1c008e4c:	00b737b3          	sltu	a5,a4,a1
1c008e50:	97b6                	add	a5,a5,a3
1c008e52:	03f7d5b3          	divu	a1,a5,t6
1c008e56:	00375613          	srli	a2,a4,0x3
1c008e5a:	00259693          	slli	a3,a1,0x2
1c008e5e:	96ae                	add	a3,a3,a1
1c008e60:	8f95                	sub	a5,a5,a3
1c008e62:	07f6                	slli	a5,a5,0x1d
1c008e64:	8e5d                	or	a2,a2,a5
1c008e66:	03f65633          	divu	a2,a2,t6
1c008e6a:	00361693          	slli	a3,a2,0x3
1c008e6e:	00561793          	slli	a5,a2,0x5
1c008e72:	97b6                	add	a5,a5,a3
1c008e74:	40f707b3          	sub	a5,a4,a5
1c008e78:	03f7d7b3          	divu	a5,a5,t6
1c008e7c:	01d65713          	srli	a4,a2,0x1d
1c008e80:	972e                	add	a4,a4,a1
1c008e82:	96be                	add	a3,a3,a5
1c008e84:	00f6b7b3          	sltu	a5,a3,a5
1c008e88:	973e                	add	a4,a4,a5
1c008e8a:	01f71613          	slli	a2,a4,0x1f
1c008e8e:	0016d793          	srli	a5,a3,0x1
1c008e92:	8fd1                	or	a5,a5,a2
1c008e94:	fc16b6b3          	p.bclr	a3,a3,30,1
1c008e98:	00f685b3          	add	a1,a3,a5
1c008e9c:	8305                	srli	a4,a4,0x1
1c008e9e:	00d5b6b3          	sltu	a3,a1,a3
1c008ea2:	96ba                	add	a3,a3,a4
1c008ea4:	95f6                	add	a1,a1,t4
1c008ea6:	96aa                	add	a3,a3,a0
1c008ea8:	01d5beb3          	sltu	t4,a1,t4
1c008eac:	00de8533          	add	a0,t4,a3
1c008eb0:	f6053633          	p.bclr	a2,a0,27,0
1c008eb4:	86ae                	mv	a3,a1
1c008eb6:	c22d                	beqz	a2,1c008f18 <pos_libc_prf+0x772>
1c008eb8:	00258613          	addi	a2,a1,2
1c008ebc:	00b636b3          	sltu	a3,a2,a1
1c008ec0:	96aa                	add	a3,a3,a0
1c008ec2:	4e95                	li	t4,5
1c008ec4:	03d6d333          	divu	t1,a3,t4
1c008ec8:	00365513          	srli	a0,a2,0x3
1c008ecc:	0805                	addi	a6,a6,1
1c008ece:	00231593          	slli	a1,t1,0x2
1c008ed2:	959a                	add	a1,a1,t1
1c008ed4:	8e8d                	sub	a3,a3,a1
1c008ed6:	06f6                	slli	a3,a3,0x1d
1c008ed8:	8d55                	or	a0,a0,a3
1c008eda:	03d55533          	divu	a0,a0,t4
1c008ede:	00351593          	slli	a1,a0,0x3
1c008ee2:	00551693          	slli	a3,a0,0x5
1c008ee6:	96ae                	add	a3,a3,a1
1c008ee8:	40d606b3          	sub	a3,a2,a3
1c008eec:	03d6d6b3          	divu	a3,a3,t4
1c008ef0:	8175                	srli	a0,a0,0x1d
1c008ef2:	951a                	add	a0,a0,t1
1c008ef4:	95b6                	add	a1,a1,a3
1c008ef6:	00d5b6b3          	sltu	a3,a1,a3
1c008efa:	00a68633          	add	a2,a3,a0
1c008efe:	01f61513          	slli	a0,a2,0x1f
1c008f02:	0015d693          	srli	a3,a1,0x1
1c008f06:	8ec9                	or	a3,a3,a0
1c008f08:	fc15b5b3          	p.bclr	a1,a1,30,1
1c008f0c:	96ae                	add	a3,a3,a1
1c008f0e:	8205                	srli	a2,a2,0x1
1c008f10:	00b6b5b3          	sltu	a1,a3,a1
1c008f14:	00c58533          	add	a0,a1,a2
1c008f18:	06600593          	li	a1,102
1c008f1c:	00188613          	addi	a2,a7,1
1c008f20:	60b48463          	beq	s1,a1,1c009528 <pos_libc_prf+0xd82>
1c008f24:	00269593          	slli	a1,a3,0x2
1c008f28:	01e6de93          	srli	t4,a3,0x1e
1c008f2c:	00251313          	slli	t1,a0,0x2
1c008f30:	96ae                	add	a3,a3,a1
1c008f32:	006ee333          	or	t1,t4,t1
1c008f36:	00b6b5b3          	sltu	a1,a3,a1
1c008f3a:	951a                	add	a0,a0,t1
1c008f3c:	952e                	add	a0,a0,a1
1c008f3e:	0506                	slli	a0,a0,0x1
1c008f40:	01f6d593          	srli	a1,a3,0x1f
1c008f44:	8d4d                	or	a0,a0,a1
1c008f46:	01c55593          	srli	a1,a0,0x1c
1c008f4a:	03058313          	addi	t1,a1,48
1c008f4e:	47b2                	lw	a5,12(sp)
1c008f50:	10000737          	lui	a4,0x10000
1c008f54:	00b035b3          	snez	a1,a1
1c008f58:	177d                	addi	a4,a4,-1
1c008f5a:	00688023          	sb	t1,0(a7)
1c008f5e:	0686                	slli	a3,a3,0x1
1c008f60:	8d79                	and	a0,a0,a4
1c008f62:	40b80833          	sub	a6,a6,a1
1c008f66:	5a078863          	beqz	a5,1c009516 <pos_libc_prf+0xd70>
1c008f6a:	02e00613          	li	a2,46
1c008f6e:	00c880a3          	sb	a2,1(a7)
1c008f72:	00288613          	addi	a2,a7,2
1c008f76:	040a0b63          	beqz	s4,1c008fcc <pos_libc_prf+0x826>
1c008f7a:	8332                	mv	t1,a2
1c008f7c:	9a32                	add	s4,s4,a2
1c008f7e:	4ebd                	li	t4,15
1c008f80:	03000f13          	li	t5,48
1c008f84:	00269793          	slli	a5,a3,0x2
1c008f88:	01e6d593          	srli	a1,a3,0x1e
1c008f8c:	00251713          	slli	a4,a0,0x2
1c008f90:	00d78633          	add	a2,a5,a3
1c008f94:	8f4d                	or	a4,a4,a1
1c008f96:	972a                	add	a4,a4,a0
1c008f98:	00f637b3          	sltu	a5,a2,a5
1c008f9c:	97ba                	add	a5,a5,a4
1c008f9e:	0786                	slli	a5,a5,0x1
1c008fa0:	01f65713          	srli	a4,a2,0x1f
1c008fa4:	8fd9                	or	a5,a5,a4
1c008fa6:	01c7d713          	srli	a4,a5,0x1c
1c008faa:	03070713          	addi	a4,a4,48 # 10000030 <__l2_shared_end+0x28>
1c008fae:	2fd05463          	blez	t4,1c009296 <pos_libc_prf+0xaf0>
1c008fb2:	100005b7          	lui	a1,0x10000
1c008fb6:	15fd                	addi	a1,a1,-1
1c008fb8:	00e300ab          	p.sb	a4,1(t1!)
1c008fbc:	1efd                	addi	t4,t4,-1
1c008fbe:	00161693          	slli	a3,a2,0x1
1c008fc2:	00b7f533          	and	a0,a5,a1
1c008fc6:	fa6a1fe3          	bne	s4,t1,1c008f84 <pos_libc_prf+0x7de>
1c008fca:	8652                	mv	a2,s4
1c008fcc:	0c0e1163          	bnez	t3,1c00908e <pos_libc_prf+0x8e8>
1c008fd0:	c054b6b3          	p.bclr	a3,s1,0,5
1c008fd4:	04500593          	li	a1,69
1c008fd8:	02b69963          	bne	a3,a1,1c00900a <pos_libc_prf+0x864>
1c008fdc:	87a6                	mv	a5,s1
1c008fde:	00f60023          	sb	a5,0(a2)
1c008fe2:	5e084d63          	bltz	a6,1c0095dc <pos_libc_prf+0xe36>
1c008fe6:	02b00793          	li	a5,43
1c008fea:	00f600a3          	sb	a5,1(a2)
1c008fee:	47a9                	li	a5,10
1c008ff0:	02f846b3          	div	a3,a6,a5
1c008ff4:	0611                	addi	a2,a2,4
1c008ff6:	02f867b3          	rem	a5,a6,a5
1c008ffa:	03068693          	addi	a3,a3,48 # 8000030 <__l1_heap_size+0x7ff0038>
1c008ffe:	fed60f23          	sb	a3,-2(a2)
1c009002:	03078793          	addi	a5,a5,48
1c009006:	fef60fa3          	sb	a5,-1(a2)
1c00900a:	00060023          	sb	zero,0(a2)
1c00900e:	419604b3          	sub	s1,a2,s9
1c009012:	46d2                	lw	a3,20(sp)
1c009014:	4762                	lw	a4,24(sp)
1c009016:	8ed9                	or	a3,a3,a4
1c009018:	c636                	sw	a3,12(sp)
1c00901a:	2a069463          	bnez	a3,1c0092c2 <pos_libc_prf+0xb1c>
1c00901e:	02414683          	lbu	a3,36(sp)
1c009022:	02d00793          	li	a5,45
1c009026:	28f68e63          	beq	a3,a5,1c0092c2 <pos_libc_prf+0xb1c>
1c00902a:	0c800793          	li	a5,200
1c00902e:	9c97dde3          	ble	s1,a5,1c008a08 <pos_libc_prf+0x262>
1c009032:	547d                	li	s0,-1
1c009034:	fdeff06f          	j	1c008812 <pos_libc_prf+0x6c>
1c009038:	0305                	addi	t1,t1,1
1c00903a:	00269793          	slli	a5,a3,0x2
1c00903e:	01e6d893          	srli	a7,a3,0x1e
1c009042:	00251713          	slli	a4,a0,0x2
1c009046:	00d785b3          	add	a1,a5,a3
1c00904a:	00e8e733          	or	a4,a7,a4
1c00904e:	972a                	add	a4,a4,a0
1c009050:	00f5b7b3          	sltu	a5,a1,a5
1c009054:	97ba                	add	a5,a5,a4
1c009056:	0786                	slli	a5,a5,0x1
1c009058:	01f5d713          	srli	a4,a1,0x1f
1c00905c:	8fd9                	or	a5,a5,a4
1c00905e:	01c7d893          	srli	a7,a5,0x1c
1c009062:	03000713          	li	a4,48
1c009066:	01d05c63          	blez	t4,1c00907e <pos_libc_prf+0x8d8>
1c00906a:	00159693          	slli	a3,a1,0x1
1c00906e:	100005b7          	lui	a1,0x10000
1c009072:	15fd                	addi	a1,a1,-1
1c009074:	03088713          	addi	a4,a7,48
1c009078:	1efd                	addi	t4,t4,-1
1c00907a:	00b7f533          	and	a0,a5,a1
1c00907e:	fee30fa3          	sb	a4,-1(t1)
1c009082:	fa661be3          	bne	a2,t1,1c009038 <pos_libc_prf+0x892>
1c009086:	014f8633          	add	a2,t6,s4
1c00908a:	f80e00e3          	beqz	t3,1c00900a <pos_libc_prf+0x864>
1c00908e:	03000513          	li	a0,48
1c009092:	a011                	j	1c009096 <pos_libc_prf+0x8f0>
1c009094:	8636                	mv	a2,a3
1c009096:	fff60693          	addi	a3,a2,-1
1c00909a:	0006c583          	lbu	a1,0(a3)
1c00909e:	fea58be3          	beq	a1,a0,1c009094 <pos_libc_prf+0x8ee>
1c0090a2:	02e00513          	li	a0,46
1c0090a6:	f2a595e3          	bne	a1,a0,1c008fd0 <pos_libc_prf+0x82a>
1c0090aa:	8636                	mv	a2,a3
1c0090ac:	b715                	j	1c008fd0 <pos_libc_prf+0x82a>
1c0090ae:	00f680ab          	p.sb	a5,1(a3!)
1c0090b2:	8c051ce3          	bnez	a0,1c00898a <pos_libc_prf+0x1e4>
1c0090b6:	b8c5                	j	1c0089a6 <pos_libc_prf+0x200>
1c0090b8:	8dba                	mv	s11,a4
1c0090ba:	f34ff06f          	j	1c0087ee <pos_libc_prf+0x48>
1c0090be:	77e1                	lui	a5,0xffff8
1c0090c0:	8307c793          	xori	a5,a5,-2000
1c0090c4:	02610693          	addi	a3,sp,38
1c0090c8:	000c2583          	lw	a1,0(s8)
1c0090cc:	02f11223          	sh	a5,36(sp)
1c0090d0:	0c11                	addi	s8,s8,4
1c0090d2:	87b6                	mv	a5,a3
1c0090d4:	48a5                	li	a7,9
1c0090d6:	f645b633          	p.bclr	a2,a1,27,4
1c0090da:	0ff67713          	andi	a4,a2,255
1c0090de:	03070513          	addi	a0,a4,48
1c0090e2:	8191                	srli	a1,a1,0x4
1c0090e4:	05770713          	addi	a4,a4,87
1c0090e8:	06c8e863          	bltu	a7,a2,1c009158 <pos_libc_prf+0x9b2>
1c0090ec:	00a780ab          	p.sb	a0,1(a5!) # ffff8001 <pulp__FC+0xffff8002>
1c0090f0:	f1fd                	bnez	a1,1c0090d6 <pos_libc_prf+0x930>
1c0090f2:	40d78733          	sub	a4,a5,a3
1c0090f6:	461d                	li	a2,7
1c0090f8:	02e64563          	blt	a2,a4,1c009122 <pos_libc_prf+0x97c>
1c0090fc:	1998                	addi	a4,sp,240
1c0090fe:	40e78533          	sub	a0,a5,a4
1c009102:	40f68633          	sub	a2,a3,a5
1c009106:	0cb50513          	addi	a0,a0,203
1c00910a:	4821                	li	a6,8
1c00910c:	03000593          	li	a1,48
1c009110:	0621                	addi	a2,a2,8
1c009112:	5aa84263          	blt	a6,a0,1c0096b6 <pos_libc_prf+0xf10>
1c009116:	004640fb          	lp.setup	x1,a2,1c00911e <pos_libc_prf+0x978>
1c00911a:	00b780ab          	p.sb	a1,1(a5!)
1c00911e:	40d78733          	sub	a4,a5,a3
1c009122:	fe078fab          	p.sb	zero,-1(a5!)
1c009126:	00f6fc63          	bleu	a5,a3,1c00913e <pos_libc_prf+0x998>
1c00912a:	0006c583          	lbu	a1,0(a3)
1c00912e:	0007c603          	lbu	a2,0(a5)
1c009132:	feb78fab          	p.sb	a1,-1(a5!)
1c009136:	00c680ab          	p.sb	a2,1(a3!)
1c00913a:	fef6e8e3          	bltu	a3,a5,1c00912a <pos_libc_prf+0x984>
1c00913e:	00270493          	addi	s1,a4,2
1c009142:	0c800793          	li	a5,200
1c009146:	17fa2963          	p.beqimm	s4,-1,1c0092b8 <pos_libc_prf+0xb12>
1c00914a:	9c97c1e3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c00914e:	02000713          	li	a4,32
1c009152:	c602                	sw	zero,12(sp)
1c009154:	c83a                	sw	a4,16(sp)
1c009156:	b84d                	j	1c008a08 <pos_libc_prf+0x262>
1c009158:	00e780ab          	p.sb	a4,1(a5!)
1c00915c:	fdad                	bnez	a1,1c0090d6 <pos_libc_prf+0x930>
1c00915e:	bf51                	j	1c0090f2 <pos_libc_prf+0x94c>
1c009160:	000c2783          	lw	a5,0(s8)
1c009164:	0c11                	addi	s8,s8,4
1c009166:	01b7a023          	sw	s11,0(a5)
1c00916a:	e84ff06f          	j	1c0087ee <pos_libc_prf+0x48>
1c00916e:	06900693          	li	a3,105
1c009172:	12d49863          	bne	s1,a3,1c0092a2 <pos_libc_prf+0xafc>
1c009176:	000c2503          	lw	a0,0(s8)
1c00917a:	0c11                	addi	s8,s8,4
1c00917c:	34054d63          	bltz	a0,1c0094d6 <pos_libc_prf+0xd30>
1c009180:	4652                	lw	a2,20(sp)
1c009182:	86aa                	mv	a3,a0
1c009184:	2e061963          	bnez	a2,1c009476 <pos_libc_prf+0xcd0>
1c009188:	4762                	lw	a4,24(sp)
1c00918a:	87e6                	mv	a5,s9
1c00918c:	c719                	beqz	a4,1c00919a <pos_libc_prf+0x9f4>
1c00918e:	02000793          	li	a5,32
1c009192:	02f10223          	sb	a5,36(sp)
1c009196:	02510793          	addi	a5,sp,37
1c00919a:	873e                	mv	a4,a5
1c00919c:	45a9                	li	a1,10
1c00919e:	02b6f633          	remu	a2,a3,a1
1c0091a2:	02b6d6b3          	divu	a3,a3,a1
1c0091a6:	03060613          	addi	a2,a2,48
1c0091aa:	00c700ab          	p.sb	a2,1(a4!)
1c0091ae:	fae5                	bnez	a3,1c00919e <pos_libc_prf+0x9f8>
1c0091b0:	40f706b3          	sub	a3,a4,a5
1c0091b4:	0146dc63          	ble	s4,a3,1c0091cc <pos_libc_prf+0xa26>
1c0091b8:	40e786b3          	sub	a3,a5,a4
1c0091bc:	03000613          	li	a2,48
1c0091c0:	96d2                	add	a3,a3,s4
1c0091c2:	0046c0fb          	lp.setup	x1,a3,1c0091ca <pos_libc_prf+0xa24>
1c0091c6:	00c700ab          	p.sb	a2,1(a4!)
1c0091ca:	0001                	nop
1c0091cc:	86ba                	mv	a3,a4
1c0091ce:	fe068fab          	p.sb	zero,-1(a3!)
1c0091d2:	00d7fc63          	bleu	a3,a5,1c0091ea <pos_libc_prf+0xa44>
1c0091d6:	0007c583          	lbu	a1,0(a5)
1c0091da:	0006c603          	lbu	a2,0(a3)
1c0091de:	feb68fab          	p.sb	a1,-1(a3!)
1c0091e2:	00c780ab          	p.sb	a2,1(a5!)
1c0091e6:	fed7e8e3          	bltu	a5,a3,1c0091d6 <pos_libc_prf+0xa30>
1c0091ea:	47d2                	lw	a5,20(sp)
1c0091ec:	4662                	lw	a2,24(sp)
1c0091ee:	419704b3          	sub	s1,a4,s9
1c0091f2:	8fd1                	or	a5,a5,a2
1c0091f4:	c63e                	sw	a5,12(sp)
1c0091f6:	e399                	bnez	a5,1c0091fc <pos_libc_prf+0xa56>
1c0091f8:	817d                	srli	a0,a0,0x1f
1c0091fa:	c62a                	sw	a0,12(sp)
1c0091fc:	e3fa27e3          	p.beqimm	s4,-1,1c00902a <pos_libc_prf+0x884>
1c009200:	0c800793          	li	a5,200
1c009204:	9097c4e3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c009208:	02000713          	li	a4,32
1c00920c:	c83a                	sw	a4,16(sp)
1c00920e:	ffaff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c009212:	000c2783          	lw	a5,0(s8)
1c009216:	020102a3          	sb	zero,37(sp)
1c00921a:	0c11                	addi	s8,s8,4
1c00921c:	02f10223          	sb	a5,36(sp)
1c009220:	4485                	li	s1,1
1c009222:	f16ff06f          	j	1c008938 <pos_libc_prf+0x192>
1c009226:	000c2683          	lw	a3,0(s8)
1c00922a:	87e6                	mv	a5,s9
1c00922c:	0c11                	addi	s8,s8,4
1c00922e:	45a9                	li	a1,10
1c009230:	02b6f733          	remu	a4,a3,a1
1c009234:	02b6d6b3          	divu	a3,a3,a1
1c009238:	03070713          	addi	a4,a4,48
1c00923c:	00e780ab          	p.sb	a4,1(a5!)
1c009240:	fae5                	bnez	a3,1c009230 <pos_libc_prf+0xa8a>
1c009242:	419784b3          	sub	s1,a5,s9
1c009246:	0144dd63          	ble	s4,s1,1c009260 <pos_libc_prf+0xaba>
1c00924a:	40fc86b3          	sub	a3,s9,a5
1c00924e:	03000613          	li	a2,48
1c009252:	96d2                	add	a3,a3,s4
1c009254:	0046c0fb          	lp.setup	x1,a3,1c00925c <pos_libc_prf+0xab6>
1c009258:	00c780ab          	p.sb	a2,1(a5!)
1c00925c:	419784b3          	sub	s1,a5,s9
1c009260:	fe078fab          	p.sb	zero,-1(a5!)
1c009264:	00fcfd63          	bleu	a5,s9,1c00927e <pos_libc_prf+0xad8>
1c009268:	86e6                	mv	a3,s9
1c00926a:	0006c603          	lbu	a2,0(a3)
1c00926e:	0007c703          	lbu	a4,0(a5)
1c009272:	fec78fab          	p.sb	a2,-1(a5!)
1c009276:	00e680ab          	p.sb	a4,1(a3!)
1c00927a:	fef6e8e3          	bltu	a3,a5,1c00926a <pos_libc_prf+0xac4>
1c00927e:	0c800793          	li	a5,200
1c009282:	03fa2b63          	p.beqimm	s4,-1,1c0092b8 <pos_libc_prf+0xb12>
1c009286:	8897c3e3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c00928a:	02000693          	li	a3,32
1c00928e:	c602                	sw	zero,12(sp)
1c009290:	c836                	sw	a3,16(sp)
1c009292:	f76ff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c009296:	01e300ab          	p.sb	t5,1(t1!)
1c00929a:	ce6a15e3          	bne	s4,t1,1c008f84 <pos_libc_prf+0x7de>
1c00929e:	8652                	mv	a2,s4
1c0092a0:	b335                	j	1c008fcc <pos_libc_prf+0x826>
1c0092a2:	0c800693          	li	a3,200
1c0092a6:	d496d463          	ble	s1,a3,1c0087ee <pos_libc_prf+0x48>
1c0092aa:	547d                	li	s0,-1
1c0092ac:	d66ff06f          	j	1c008812 <pos_libc_prf+0x6c>
1c0092b0:	e60a5b63          	bgez	s4,1c008926 <pos_libc_prf+0x180>
1c0092b4:	e76ff06f          	j	1c00892a <pos_libc_prf+0x184>
1c0092b8:	8497cae3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c0092bc:	c602                	sw	zero,12(sp)
1c0092be:	f4aff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c0092c2:	0c800793          	li	a5,200
1c0092c6:	8497c3e3          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c0092ca:	4685                	li	a3,1
1c0092cc:	c636                	sw	a3,12(sp)
1c0092ce:	f3aff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c0092d2:	409909b3          	sub	s3,s2,s1
1c0092d6:	00148613          	addi	a2,s1,1
1c0092da:	85e6                	mv	a1,s9
1c0092dc:	013c8533          	add	a0,s9,s3
1c0092e0:	9eaff0ef          	jal	ra,1c0084ca <memmove>
1c0092e4:	46c2                	lw	a3,16(sp)
1c0092e6:	02000793          	li	a5,32
1c0092ea:	32f68b63          	beq	a3,a5,1c009620 <pos_libc_prf+0xe7a>
1c0092ee:	4732                	lw	a4,12(sp)
1c0092f0:	84ca                	mv	s1,s2
1c0092f2:	99ba                	add	s3,s3,a4
1c0092f4:	ff375b63          	ble	s3,a4,1c008aea <pos_libc_prf+0x344>
1c0092f8:	46b2                	lw	a3,12(sp)
1c0092fa:	4595                	li	a1,5
1c0092fc:	00dc87b3          	add	a5,s9,a3
1c009300:	40f007b3          	neg	a5,a5
1c009304:	fa27b7b3          	p.bclr	a5,a5,29,2
1c009308:	00378613          	addi	a2,a5,3
1c00930c:	fff98693          	addi	a3,s3,-1
1c009310:	04b67633          	p.maxu	a2,a2,a1
1c009314:	8e99                	sub	a3,a3,a4
1c009316:	40e985b3          	sub	a1,s3,a4
1c00931a:	06c6e763          	bltu	a3,a2,1c009388 <pos_libc_prf+0xbe2>
1c00931e:	863a                	mv	a2,a4
1c009320:	cf95                	beqz	a5,1c00935c <pos_libc_prf+0xbb6>
1c009322:	1990                	addi	a2,sp,240
1c009324:	00e606b3          	add	a3,a2,a4
1c009328:	4742                	lw	a4,16(sp)
1c00932a:	f2e68a23          	sb	a4,-204(a3)
1c00932e:	46b2                	lw	a3,12(sp)
1c009330:	00168613          	addi	a2,a3,1
1c009334:	0217a463          	p.beqimm	a5,1,1c00935c <pos_libc_prf+0xbb6>
1c009338:	86ba                	mv	a3,a4
1c00933a:	1998                	addi	a4,sp,240
1c00933c:	963a                	add	a2,a2,a4
1c00933e:	4732                	lw	a4,12(sp)
1c009340:	f2d60a23          	sb	a3,-204(a2)
1c009344:	00270613          	addi	a2,a4,2
1c009348:	0037ba63          	p.bneimm	a5,3,1c00935c <pos_libc_prf+0xbb6>
1c00934c:	8736                	mv	a4,a3
1c00934e:	1994                	addi	a3,sp,240
1c009350:	9636                	add	a2,a2,a3
1c009352:	46b2                	lw	a3,12(sp)
1c009354:	f2e60a23          	sb	a4,-204(a2)
1c009358:	00368613          	addi	a2,a3,3
1c00935c:	4732                	lw	a4,12(sp)
1c00935e:	8d9d                	sub	a1,a1,a5
1c009360:	0025d693          	srli	a3,a1,0x2
1c009364:	97ba                	add	a5,a5,a4
1c009366:	4742                	lw	a4,16(sp)
1c009368:	97e6                	add	a5,a5,s9
1c00936a:	00e05557          	pv.add.sc.b	a0,zero,a4
1c00936e:	34068663          	beqz	a3,1c0096ba <pos_libc_prf+0xf14>
1c009372:	0046c0fb          	lp.setup	x1,a3,1c00937a <pos_libc_prf+0xbd4>
1c009376:	00a7a22b          	p.sw	a0,4(a5!)
1c00937a:	0001                	nop
1c00937c:	c205b7b3          	p.bclr	a5,a1,1,0
1c009380:	963e                	add	a2,a2,a5
1c009382:	c632                	sw	a2,12(sp)
1c009384:	f6b78263          	beq	a5,a1,1c008ae8 <pos_libc_prf+0x342>
1c009388:	46b2                	lw	a3,12(sp)
1c00938a:	4742                	lw	a4,16(sp)
1c00938c:	198c                	addi	a1,sp,240
1c00938e:	00d587b3          	add	a5,a1,a3
1c009392:	f2e78a23          	sb	a4,-204(a5)
1c009396:	00168793          	addi	a5,a3,1
1c00939a:	f537d763          	ble	s3,a5,1c008ae8 <pos_libc_prf+0x342>
1c00939e:	97ae                	add	a5,a5,a1
1c0093a0:	f2e78a23          	sb	a4,-204(a5)
1c0093a4:	00268793          	addi	a5,a3,2
1c0093a8:	f537d063          	ble	s3,a5,1c008ae8 <pos_libc_prf+0x342>
1c0093ac:	97ae                	add	a5,a5,a1
1c0093ae:	f2e78a23          	sb	a4,-204(a5)
1c0093b2:	00368793          	addi	a5,a3,3
1c0093b6:	f337d963          	ble	s3,a5,1c008ae8 <pos_libc_prf+0x342>
1c0093ba:	97ae                	add	a5,a5,a1
1c0093bc:	f2e78a23          	sb	a4,-204(a5)
1c0093c0:	00468793          	addi	a5,a3,4
1c0093c4:	f337d263          	ble	s3,a5,1c008ae8 <pos_libc_prf+0x342>
1c0093c8:	97ae                	add	a5,a5,a1
1c0093ca:	f2e78a23          	sb	a4,-204(a5)
1c0093ce:	00568a93          	addi	s5,a3,5
1c0093d2:	f13adb63          	ble	s3,s5,1c008ae8 <pos_libc_prf+0x342>
1c0093d6:	9aae                	add	s5,s5,a1
1c0093d8:	f2ea8a23          	sb	a4,-204(s5)
1c0093dc:	84ca                	mv	s1,s2
1c0093de:	f0cff06f          	j	1c008aea <pos_libc_prf+0x344>
1c0093e2:	4301                	li	t1,0
1c0093e4:	8666                	mv	a2,s9
1c0093e6:	da0ff06f          	j	1c008986 <pos_libc_prf+0x1e0>
1c0093ea:	02414783          	lbu	a5,36(sp)
1c0093ee:	1054                	addi	a3,sp,36
1c0093f0:	4665                	li	a2,25
1c0093f2:	de078b63          	beqz	a5,1c0089e8 <pos_libc_prf+0x242>
1c0093f6:	fe078593          	addi	a1,a5,-32
1c0093fa:	f9f78793          	addi	a5,a5,-97
1c0093fe:	0ff7f793          	andi	a5,a5,255
1c009402:	00f66963          	bltu	a2,a5,1c009414 <pos_libc_prf+0xc6e>
1c009406:	00b680ab          	p.sb	a1,1(a3!)
1c00940a:	0006c783          	lbu	a5,0(a3)
1c00940e:	f7e5                	bnez	a5,1c0093f6 <pos_libc_prf+0xc50>
1c009410:	dd8ff06f          	j	1c0089e8 <pos_libc_prf+0x242>
1c009414:	0685                	addi	a3,a3,1
1c009416:	0006c783          	lbu	a5,0(a3)
1c00941a:	fff1                	bnez	a5,1c0093f6 <pos_libc_prf+0xc50>
1c00941c:	dccff06f          	j	1c0089e8 <pos_libc_prf+0x242>
1c009420:	ee97c663          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c009424:	8c46                	mv	s8,a7
1c009426:	de2ff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c00942a:	020102a3          	sb	zero,37(sp)
1c00942e:	8c42                	mv	s8,a6
1c009430:	44b2                	lw	s1,12(sp)
1c009432:	d1fa2363          	p.beqimm	s4,-1,1c008938 <pos_libc_prf+0x192>
1c009436:	02000693          	li	a3,32
1c00943a:	c836                	sw	a3,16(sp)
1c00943c:	cfcff06f          	j	1c008938 <pos_libc_prf+0x192>
1c009440:	8566                	mv	a0,s9
1c009442:	86e6                	mv	a3,s9
1c009444:	fb6ff06f          	j	1c008bfa <pos_libc_prf+0x454>
1c009448:	4732                	lw	a4,12(sp)
1c00944a:	4e01                	li	t3,0
1c00944c:	e319                	bnez	a4,1c009452 <pos_libc_prf+0xcac>
1c00944e:	01403e33          	snez	t3,s4
1c009452:	5675                	li	a2,-3
1c009454:	001a0693          	addi	a3,s4,1
1c009458:	00c84463          	blt	a6,a2,1c009460 <pos_libc_prf+0xcba>
1c00945c:	1706d063          	ble	a6,a3,1c0095bc <pos_libc_prf+0xe16>
1c009460:	47c1                	li	a5,16
1c009462:	04f6cf33          	p.min	t5,a3,a5
1c009466:	06700693          	li	a3,103
1c00946a:	1f7d                	addi	t5,t5,-1
1c00946c:	1ed48a63          	beq	s1,a3,1c009660 <pos_libc_prf+0xeba>
1c009470:	04500493          	li	s1,69
1c009474:	b2d9                	j	1c008e3a <pos_libc_prf+0x694>
1c009476:	02b00793          	li	a5,43
1c00947a:	02f10223          	sb	a5,36(sp)
1c00947e:	02510793          	addi	a5,sp,37
1c009482:	bb21                	j	1c00919a <pos_libc_prf+0x9f4>
1c009484:	8666                	mv	a2,s9
1c009486:	1a084063          	bltz	a6,1c009626 <pos_libc_prf+0xe80>
1c00948a:	8ecd                	or	a3,a3,a1
1c00948c:	fbf48793          	addi	a5,s1,-65
1c009490:	00360713          	addi	a4,a2,3
1c009494:	14069b63          	bnez	a3,1c0095ea <pos_libc_prf+0xe44>
1c009498:	46e5                	li	a3,25
1c00949a:	1af6e563          	bltu	a3,a5,1c009644 <pos_libc_prf+0xe9e>
1c00949e:	6795                	lui	a5,0x5
1c0094a0:	e4978793          	addi	a5,a5,-439 # 4e49 <__cluster_text_size+0x4e49>
1c0094a4:	00f61023          	sh	a5,0(a2)
1c0094a8:	04600793          	li	a5,70
1c0094ac:	00f60123          	sb	a5,2(a2)
1c0094b0:	000601a3          	sb	zero,3(a2)
1c0094b4:	419704b3          	sub	s1,a4,s9
1c0094b8:	bea9                	j	1c009012 <pos_libc_prf+0x86c>
1c0094ba:	46d2                	lw	a3,20(sp)
1c0094bc:	14068463          	beqz	a3,1c009604 <pos_libc_prf+0xe5e>
1c0094c0:	02b00693          	li	a3,43
1c0094c4:	02d10223          	sb	a3,36(sp)
1c0094c8:	02510893          	addi	a7,sp,37
1c0094cc:	4801                	li	a6,0
1c0094ce:	4501                	li	a0,0
1c0094d0:	4681                	li	a3,0
1c0094d2:	4301                	li	t1,0
1c0094d4:	ba09                	j	1c008de6 <pos_libc_prf+0x640>
1c0094d6:	02d00793          	li	a5,45
1c0094da:	02f10223          	sb	a5,36(sp)
1c0094de:	800007b7          	lui	a5,0x80000
1c0094e2:	1af50963          	beq	a0,a5,1c009694 <pos_libc_prf+0xeee>
1c0094e6:	40a006b3          	neg	a3,a0
1c0094ea:	02510793          	addi	a5,sp,37
1c0094ee:	b175                	j	1c00919a <pos_libc_prf+0x9f4>
1c0094f0:	4a19                	li	s4,6
1c0094f2:	92d495e3          	bne	s1,a3,1c008e1c <pos_libc_prf+0x676>
1c0094f6:	46b2                	lw	a3,12(sp)
1c0094f8:	57f5                	li	a5,-3
1c0094fa:	0016ce13          	xori	t3,a3,1
1c0094fe:	14f85d63          	ble	a5,a6,1c009658 <pos_libc_prf+0xeb2>
1c009502:	06500493          	li	s1,101
1c009506:	4f19                	li	t5,6
1c009508:	ba0d                	j	1c008e3a <pos_libc_prf+0x694>
1c00950a:	e097c163          	blt	a5,s1,1c008b0c <pos_libc_prf+0x366>
1c00950e:	8c42                	mv	s8,a6
1c009510:	c602                	sw	zero,12(sp)
1c009512:	cf6ff06f          	j	1c008a08 <pos_libc_prf+0x262>
1c009516:	aa0a0be3          	beqz	s4,1c008fcc <pos_libc_prf+0x826>
1c00951a:	02e00593          	li	a1,46
1c00951e:	00288613          	addi	a2,a7,2
1c009522:	00b880a3          	sb	a1,1(a7)
1c009526:	bc91                	j	1c008f7a <pos_libc_prf+0x7d4>
1c009528:	17005b63          	blez	a6,1c00969e <pos_libc_prf+0xef8>
1c00952c:	9846                	add	a6,a6,a7
1c00952e:	4ec1                	li	t4,16
1c009530:	03000f13          	li	t5,48
1c009534:	00269793          	slli	a5,a3,0x2
1c009538:	01e6d593          	srli	a1,a3,0x1e
1c00953c:	00251713          	slli	a4,a0,0x2
1c009540:	00d78633          	add	a2,a5,a3
1c009544:	8f4d                	or	a4,a4,a1
1c009546:	972a                	add	a4,a4,a0
1c009548:	00f637b3          	sltu	a5,a2,a5
1c00954c:	97ba                	add	a5,a5,a4
1c00954e:	0786                	slli	a5,a5,0x1
1c009550:	01f65713          	srli	a4,a2,0x1f
1c009554:	8fd9                	or	a5,a5,a4
1c009556:	01c7d713          	srli	a4,a5,0x1c
1c00955a:	03070713          	addi	a4,a4,48
1c00955e:	05d05963          	blez	t4,1c0095b0 <pos_libc_prf+0xe0a>
1c009562:	00e880ab          	p.sb	a4,1(a7!)
1c009566:	10000737          	lui	a4,0x10000
1c00956a:	177d                	addi	a4,a4,-1
1c00956c:	1efd                	addi	t4,t4,-1
1c00956e:	00161693          	slli	a3,a2,0x1
1c009572:	00e7f533          	and	a0,a5,a4
1c009576:	fb181fe3          	bne	a6,a7,1c009534 <pos_libc_prf+0xd8e>
1c00957a:	8642                	mv	a2,a6
1c00957c:	4801                	li	a6,0
1c00957e:	47b2                	lw	a5,12(sp)
1c009580:	e399                	bnez	a5,1c009586 <pos_libc_prf+0xde0>
1c009582:	b00a04e3          	beqz	s4,1c00908a <pos_libc_prf+0x8e4>
1c009586:	00160f93          	addi	t6,a2,1
1c00958a:	001a0593          	addi	a1,s4,1
1c00958e:	02e00893          	li	a7,46
1c009592:	01160023          	sb	a7,0(a2)
1c009596:	837e                	mv	t1,t6
1c009598:	962e                	add	a2,a2,a1
1c00959a:	03000593          	li	a1,48
1c00959e:	aec304e3          	beq	t1,a2,1c009086 <pos_libc_prf+0x8e0>
1c0095a2:	0305                	addi	t1,t1,1
1c0095a4:	a8080be3          	beqz	a6,1c00903a <pos_libc_prf+0x894>
1c0095a8:	feb30fa3          	sb	a1,-1(t1)
1c0095ac:	0805                	addi	a6,a6,1
1c0095ae:	bfc5                	j	1c00959e <pos_libc_prf+0xdf8>
1c0095b0:	01e880ab          	p.sb	t5,1(a7!)
1c0095b4:	f91810e3          	bne	a6,a7,1c009534 <pos_libc_prf+0xd8e>
1c0095b8:	b7c9                	j	1c00957a <pos_libc_prf+0xdd4>
1c0095ba:	4e01                	li	t3,0
1c0095bc:	014807b3          	add	a5,a6,s4
1c0095c0:	0e07c563          	bltz	a5,1c0096aa <pos_libc_prf+0xf04>
1c0095c4:	4641                	li	a2,16
1c0095c6:	04c7cf33          	p.min	t5,a5,a2
1c0095ca:	1f7d                	addi	t5,t5,-1
1c0095cc:	06600493          	li	s1,102
1c0095d0:	860795e3          	bnez	a5,1c008e3a <pos_libc_prf+0x694>
1c0095d4:	4581                	li	a1,0
1c0095d6:	080006b7          	lui	a3,0x8000
1c0095da:	b0e9                	j	1c008ea4 <pos_libc_prf+0x6fe>
1c0095dc:	02d00793          	li	a5,45
1c0095e0:	41000833          	neg	a6,a6
1c0095e4:	00f600a3          	sb	a5,1(a2)
1c0095e8:	b419                	j	1c008fee <pos_libc_prf+0x848>
1c0095ea:	46e5                	li	a3,25
1c0095ec:	06f6ee63          	bltu	a3,a5,1c009668 <pos_libc_prf+0xec2>
1c0095f0:	6791                	lui	a5,0x4
1c0095f2:	14e78793          	addi	a5,a5,334 # 414e <__cluster_text_size+0x414e>
1c0095f6:	00f61023          	sh	a5,0(a2)
1c0095fa:	04e00793          	li	a5,78
1c0095fe:	00f60123          	sb	a5,2(a2)
1c009602:	b57d                	j	1c0094b0 <pos_libc_prf+0xd0a>
1c009604:	47e2                	lw	a5,24(sp)
1c009606:	cfc5                	beqz	a5,1c0096be <pos_libc_prf+0xf18>
1c009608:	02000693          	li	a3,32
1c00960c:	02d10223          	sb	a3,36(sp)
1c009610:	02510893          	addi	a7,sp,37
1c009614:	4801                	li	a6,0
1c009616:	4501                	li	a0,0
1c009618:	4681                	li	a3,0
1c00961a:	4301                	li	t1,0
1c00961c:	fcaff06f          	j	1c008de6 <pos_libc_prf+0x640>
1c009620:	c602                	sw	zero,12(sp)
1c009622:	4732                	lw	a4,12(sp)
1c009624:	b9d1                	j	1c0092f8 <pos_libc_prf+0xb52>
1c009626:	02d00613          	li	a2,45
1c00962a:	02c10223          	sb	a2,36(sp)
1c00962e:	02510613          	addi	a2,sp,37
1c009632:	bda1                	j	1c00948a <pos_libc_prf+0xce4>
1c009634:	02d00613          	li	a2,45
1c009638:	02c10223          	sb	a2,36(sp)
1c00963c:	02510893          	addi	a7,sp,37
1c009640:	ec6ff06f          	j	1c008d06 <pos_libc_prf+0x560>
1c009644:	679d                	lui	a5,0x7
1c009646:	e6978793          	addi	a5,a5,-407 # 6e69 <__cluster_text_size+0x6e69>
1c00964a:	00f61023          	sh	a5,0(a2)
1c00964e:	06600793          	li	a5,102
1c009652:	00f60123          	sb	a5,2(a2)
1c009656:	bda9                	j	1c0094b0 <pos_libc_prf+0xd0a>
1c009658:	479d                	li	a5,7
1c00965a:	f707d1e3          	ble	a6,a5,1c0095bc <pos_libc_prf+0xe16>
1c00965e:	4f19                	li	t5,6
1c009660:	06500493          	li	s1,101
1c009664:	fd6ff06f          	j	1c008e3a <pos_libc_prf+0x694>
1c009668:	6799                	lui	a5,0x6
1c00966a:	16e78793          	addi	a5,a5,366 # 616e <__cluster_text_size+0x616e>
1c00966e:	00f61023          	sh	a5,0(a2)
1c009672:	06e00793          	li	a5,110
1c009676:	00f60123          	sb	a5,2(a2)
1c00967a:	bd1d                	j	1c0094b0 <pos_libc_prf+0xd0a>
1c00967c:	47e2                	lw	a5,24(sp)
1c00967e:	88e6                	mv	a7,s9
1c009680:	e8078363          	beqz	a5,1c008d06 <pos_libc_prf+0x560>
1c009684:	02000613          	li	a2,32
1c009688:	02c10223          	sb	a2,36(sp)
1c00968c:	02510893          	addi	a7,sp,37
1c009690:	e76ff06f          	j	1c008d06 <pos_libc_prf+0x560>
1c009694:	800006b7          	lui	a3,0x80000
1c009698:	02510793          	addi	a5,sp,37
1c00969c:	bcfd                	j	1c00919a <pos_libc_prf+0x9f4>
1c00969e:	03000593          	li	a1,48
1c0096a2:	00b88023          	sb	a1,0(a7)
1c0096a6:	4ec1                	li	t4,16
1c0096a8:	bdd9                	j	1c00957e <pos_libc_prf+0xdd8>
1c0096aa:	06600493          	li	s1,102
1c0096ae:	b71d                	j	1c0095d4 <pos_libc_prf+0xe2e>
1c0096b0:	4685                	li	a3,1
1c0096b2:	bc4ff06f          	j	1c008a76 <pos_libc_prf+0x2d0>
1c0096b6:	4605                	li	a2,1
1c0096b8:	bcb9                	j	1c009116 <pos_libc_prf+0x970>
1c0096ba:	4685                	li	a3,1
1c0096bc:	b95d                	j	1c009372 <pos_libc_prf+0xbcc>
1c0096be:	88e6                	mv	a7,s9
1c0096c0:	bf91                	j	1c009614 <pos_libc_prf+0xe6e>

1c0096c2 <pos_init_start>:
1c0096c2:	1141                	addi	sp,sp,-16
1c0096c4:	c422                	sw	s0,8(sp)
1c0096c6:	1c000437          	lui	s0,0x1c000
1c0096ca:	c606                	sw	ra,12(sp)
1c0096cc:	00840413          	addi	s0,s0,8 # 1c000008 <ctor_list>
1c0096d0:	c67fe0ef          	jal	ra,1c008336 <pos_soc_init>
1c0096d4:	2279                	jal	1c009862 <pos_irq_init>
1c0096d6:	2ac1                	jal	1c0098a6 <pos_soc_event_init>
1c0096d8:	20e5                	jal	1c0097c0 <pos_allocs_init>
1c0096da:	405c                	lw	a5,4(s0)
1c0096dc:	c791                	beqz	a5,1c0096e8 <pos_init_start+0x26>
1c0096de:	0421                	addi	s0,s0,8
1c0096e0:	9782                	jalr	a5
1c0096e2:	0044278b          	p.lw	a5,4(s0!)
1c0096e6:	ffed                	bnez	a5,1c0096e0 <pos_init_start+0x1e>
1c0096e8:	888ff0ef          	jal	ra,1c008770 <pos_io_start>
1c0096ec:	300467f3          	csrrsi	a5,mstatus,8
1c0096f0:	f1402573          	csrr	a0,mhartid
1c0096f4:	8515                	srai	a0,a0,0x5
1c0096f6:	f2653533          	p.bclr	a0,a0,25,6
1c0096fa:	47fd                	li	a5,31
1c0096fc:	00f50a63          	beq	a0,a5,1c009710 <pos_init_start+0x4e>
1c009700:	4422                	lw	s0,8(sp)
1c009702:	40b2                	lw	ra,12(sp)
1c009704:	1c0085b7          	lui	a1,0x1c008
1c009708:	13e58593          	addi	a1,a1,318 # 1c00813e <main>
1c00970c:	0141                	addi	sp,sp,16
1c00970e:	a405                	j	1c00992e <cluster_start>
1c009710:	40b2                	lw	ra,12(sp)
1c009712:	4422                	lw	s0,8(sp)
1c009714:	0141                	addi	sp,sp,16
1c009716:	8082                	ret

1c009718 <pos_init_stop>:
1c009718:	1141                	addi	sp,sp,-16
1c00971a:	c422                	sw	s0,8(sp)
1c00971c:	1c000437          	lui	s0,0x1c000
1c009720:	c606                	sw	ra,12(sp)
1c009722:	01440413          	addi	s0,s0,20 # 1c000014 <dtor_list>
1c009726:	84eff0ef          	jal	ra,1c008774 <pos_io_stop>
1c00972a:	405c                	lw	a5,4(s0)
1c00972c:	c791                	beqz	a5,1c009738 <pos_init_stop+0x20>
1c00972e:	0421                	addi	s0,s0,8
1c009730:	9782                	jalr	a5
1c009732:	0044278b          	p.lw	a5,4(s0!)
1c009736:	ffed                	bnez	a5,1c009730 <pos_init_stop+0x18>
1c009738:	40b2                	lw	ra,12(sp)
1c00973a:	4422                	lw	s0,8(sp)
1c00973c:	0141                	addi	sp,sp,16
1c00973e:	8082                	ret

1c009740 <pos_alloc_init>:
1c009740:	00758793          	addi	a5,a1,7
1c009744:	c407b7b3          	p.bclr	a5,a5,2,0
1c009748:	40b785b3          	sub	a1,a5,a1
1c00974c:	c11c                	sw	a5,0(a0)
1c00974e:	8e0d                	sub	a2,a2,a1
1c009750:	00c05763          	blez	a2,1c00975e <pos_alloc_init+0x1e>
1c009754:	c4063633          	p.bclr	a2,a2,2,0
1c009758:	c390                	sw	a2,0(a5)
1c00975a:	0007a223          	sw	zero,4(a5)
1c00975e:	8082                	ret

1c009760 <pos_alloc>:
1c009760:	4110                	lw	a2,0(a0)
1c009762:	059d                	addi	a1,a1,7
1c009764:	c405b5b3          	p.bclr	a1,a1,2,0
1c009768:	ca31                	beqz	a2,1c0097bc <pos_alloc+0x5c>
1c00976a:	4218                	lw	a4,0(a2)
1c00976c:	425c                	lw	a5,4(a2)
1c00976e:	02b75963          	ble	a1,a4,1c0097a0 <pos_alloc+0x40>
1c009772:	cb81                	beqz	a5,1c009782 <pos_alloc+0x22>
1c009774:	4398                	lw	a4,0(a5)
1c009776:	43d4                	lw	a3,4(a5)
1c009778:	00b75763          	ble	a1,a4,1c009786 <pos_alloc+0x26>
1c00977c:	863e                	mv	a2,a5
1c00977e:	87b6                	mv	a5,a3
1c009780:	fbf5                	bnez	a5,1c009774 <pos_alloc+0x14>
1c009782:	853e                	mv	a0,a5
1c009784:	8082                	ret
1c009786:	00b70a63          	beq	a4,a1,1c00979a <pos_alloc+0x3a>
1c00978a:	00b78533          	add	a0,a5,a1
1c00978e:	8f0d                	sub	a4,a4,a1
1c009790:	c118                	sw	a4,0(a0)
1c009792:	c154                	sw	a3,4(a0)
1c009794:	c248                	sw	a0,4(a2)
1c009796:	853e                	mv	a0,a5
1c009798:	8082                	ret
1c00979a:	c254                	sw	a3,4(a2)
1c00979c:	853e                	mv	a0,a5
1c00979e:	8082                	ret
1c0097a0:	00e58b63          	beq	a1,a4,1c0097b6 <pos_alloc+0x56>
1c0097a4:	00b606b3          	add	a3,a2,a1
1c0097a8:	8f0d                	sub	a4,a4,a1
1c0097aa:	c2dc                	sw	a5,4(a3)
1c0097ac:	c298                	sw	a4,0(a3)
1c0097ae:	87b2                	mv	a5,a2
1c0097b0:	c114                	sw	a3,0(a0)
1c0097b2:	853e                	mv	a0,a5
1c0097b4:	8082                	ret
1c0097b6:	c11c                	sw	a5,0(a0)
1c0097b8:	87b2                	mv	a5,a2
1c0097ba:	b7e1                	j	1c009782 <pos_alloc+0x22>
1c0097bc:	4781                	li	a5,0
1c0097be:	b7d1                	j	1c009782 <pos_alloc+0x22>

1c0097c0 <pos_allocs_init>:
1c0097c0:	1141                	addi	sp,sp,-16
1c0097c2:	1c0015b7          	lui	a1,0x1c001
1c0097c6:	c606                	sw	ra,12(sp)
1c0097c8:	8a858793          	addi	a5,a1,-1880 # 1c0008a8 <__l2_priv0_end>
1c0097cc:	1c008637          	lui	a2,0x1c008
1c0097d0:	04c7cc63          	blt	a5,a2,1c009828 <pos_allocs_init+0x68>
1c0097d4:	4581                	li	a1,0
1c0097d6:	4601                	li	a2,0
1c0097d8:	1c001537          	lui	a0,0x1c001
1c0097dc:	89850513          	addi	a0,a0,-1896 # 1c000898 <pos_alloc_l2>
1c0097e0:	3785                	jal	1c009740 <pos_alloc_init>
1c0097e2:	1c00a5b7          	lui	a1,0x1c00a
1c0097e6:	a0458793          	addi	a5,a1,-1532 # 1c009a04 <__l2_priv1_end>
1c0097ea:	1c010637          	lui	a2,0x1c010
1c0097ee:	02c7c963          	blt	a5,a2,1c009820 <pos_allocs_init+0x60>
1c0097f2:	4581                	li	a1,0
1c0097f4:	4601                	li	a2,0
1c0097f6:	1c001537          	lui	a0,0x1c001
1c0097fa:	89c50513          	addi	a0,a0,-1892 # 1c00089c <pos_alloc_l2+0x4>
1c0097fe:	3789                	jal	1c009740 <pos_alloc_init>
1c009800:	100005b7          	lui	a1,0x10000
1c009804:	40b2                	lw	ra,12(sp)
1c009806:	00858793          	addi	a5,a1,8 # 10000008 <__l2_shared_end>
1c00980a:	1c080637          	lui	a2,0x1c080
1c00980e:	1c001537          	lui	a0,0x1c001
1c009812:	8e1d                	sub	a2,a2,a5
1c009814:	00858593          	addi	a1,a1,8
1c009818:	8a050513          	addi	a0,a0,-1888 # 1c0008a0 <pos_alloc_l2+0x8>
1c00981c:	0141                	addi	sp,sp,16
1c00981e:	b70d                	j	1c009740 <pos_alloc_init>
1c009820:	8e1d                	sub	a2,a2,a5
1c009822:	a0458593          	addi	a1,a1,-1532
1c009826:	bfc1                	j	1c0097f6 <pos_allocs_init+0x36>
1c009828:	8e1d                	sub	a2,a2,a5
1c00982a:	8a858593          	addi	a1,a1,-1880
1c00982e:	b76d                	j	1c0097d8 <pos_allocs_init+0x18>

1c009830 <alloc_init_l1>:
1c009830:	100007b7          	lui	a5,0x10000
1c009834:	01651593          	slli	a1,a0,0x16
1c009838:	00878793          	addi	a5,a5,8 # 10000008 <__l2_shared_end>
1c00983c:	95be                	add	a1,a1,a5
1c00983e:	1c0017b7          	lui	a5,0x1c001
1c009842:	050a                	slli	a0,a0,0x2
1c009844:	6641                	lui	a2,0x10
1c009846:	89478793          	addi	a5,a5,-1900 # 1c000894 <pos_alloc_l1>
1c00984a:	ff860613          	addi	a2,a2,-8 # fff8 <__l1_heap_size>
1c00984e:	953e                	add	a0,a0,a5
1c009850:	bdc5                	j	1c009740 <pos_alloc_init>

1c009852 <pi_l1_malloc>:
1c009852:	1c0017b7          	lui	a5,0x1c001
1c009856:	050a                	slli	a0,a0,0x2
1c009858:	89478793          	addi	a5,a5,-1900 # 1c000894 <pos_alloc_l1>
1c00985c:	953e                	add	a0,a0,a5
1c00985e:	b709                	j	1c009760 <pos_alloc>

1c009860 <__rt_handle_illegal_instr>:
1c009860:	8082                	ret

1c009862 <pos_irq_init>:
1c009862:	f14027f3          	csrr	a5,mhartid
1c009866:	477d                	li	a4,31
1c009868:	ca5797b3          	p.extractu	a5,a5,5,5
1c00986c:	00e78f63          	beq	a5,a4,1c00988a <pos_irq_init+0x28>
1c009870:	002047b7          	lui	a5,0x204
1c009874:	577d                	li	a4,-1
1c009876:	cb98                	sw	a4,16(a5)
1c009878:	1c0087b7          	lui	a5,0x1c008
1c00987c:	00078793          	mv	a5,a5
1c009880:	c007c7b3          	p.bset	a5,a5,0,0
1c009884:	30579073          	csrw	mtvec,a5
1c009888:	8082                	ret
1c00988a:	1a10a7b7          	lui	a5,0x1a10a
1c00988e:	577d                	li	a4,-1
1c009890:	80e7a423          	sw	a4,-2040(a5) # 1a109808 <__l2_shared_end+0xa109800>
1c009894:	1c0087b7          	lui	a5,0x1c008
1c009898:	00078793          	mv	a5,a5
1c00989c:	c007c7b3          	p.bset	a5,a5,0,0
1c0098a0:	30579073          	csrw	mtvec,a5
1c0098a4:	8082                	ret

1c0098a6 <pos_soc_event_init>:
1c0098a6:	1a1067b7          	lui	a5,0x1a106
1c0098aa:	577d                	li	a4,-1
1c0098ac:	00478693          	addi	a3,a5,4 # 1a106004 <__l2_shared_end+0xa105ffc>
1c0098b0:	c298                	sw	a4,0(a3)
1c0098b2:	00878693          	addi	a3,a5,8
1c0098b6:	c298                	sw	a4,0(a3)
1c0098b8:	00c78693          	addi	a3,a5,12
1c0098bc:	c298                	sw	a4,0(a3)
1c0098be:	01078693          	addi	a3,a5,16
1c0098c2:	c298                	sw	a4,0(a3)
1c0098c4:	01478693          	addi	a3,a5,20
1c0098c8:	c298                	sw	a4,0(a3)
1c0098ca:	01878693          	addi	a3,a5,24
1c0098ce:	c298                	sw	a4,0(a3)
1c0098d0:	01c78693          	addi	a3,a5,28
1c0098d4:	c298                	sw	a4,0(a3)
1c0098d6:	02078793          	addi	a5,a5,32
1c0098da:	c398                	sw	a4,0(a5)
1c0098dc:	8082                	ret

1c0098de <cluster_entry_stub>:
1c0098de:	1141                	addi	sp,sp,-16
1c0098e0:	c606                	sw	ra,12(sp)
1c0098e2:	002047b7          	lui	a5,0x204
1c0098e6:	00070737          	lui	a4,0x70
1c0098ea:	c798                	sw	a4,8(a5)
1c0098ec:	0ff00713          	li	a4,255
1c0098f0:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c0098f4:	00e7a023          	sw	a4,0(a5)
1c0098f8:	00e7a623          	sw	a4,12(a5)
1c0098fc:	1c0017b7          	lui	a5,0x1c001
1c009900:	8a47a783          	lw	a5,-1884(a5) # 1c0008a4 <cluster_entry>
1c009904:	9782                	jalr	a5
1c009906:	f14027f3          	csrr	a5,mhartid
1c00990a:	f457b7b3          	p.bclr	a5,a5,26,5
1c00990e:	eb89                	bnez	a5,1c009920 <cluster_entry_stub+0x42>
1c009910:	1c001737          	lui	a4,0x1c001
1c009914:	1c0017b7          	lui	a5,0x1c001
1c009918:	86a72a23          	sw	a0,-1932(a4) # 1c000874 <cluster_retval>
1c00991c:	8607ac23          	sw	zero,-1928(a5) # 1c000878 <cluster_running>
1c009920:	002047b7          	lui	a5,0x204
1c009924:	577d                	li	a4,-1
1c009926:	c3d8                	sw	a4,4(a5)
1c009928:	0387e703          	p.elw	a4,56(a5) # 204038 <__l1_heap_size+0x1f4040>
1c00992c:	a001                	j	1c00992c <cluster_entry_stub+0x4e>

1c00992e <cluster_start>:
1c00992e:	1141                	addi	sp,sp,-16
1c009930:	1c0017b7          	lui	a5,0x1c001
1c009934:	c226                	sw	s1,4(sp)
1c009936:	84aa                	mv	s1,a0
1c009938:	4509                	li	a0,2
1c00993a:	8ab7a223          	sw	a1,-1884(a5) # 1c0008a4 <cluster_entry>
1c00993e:	c606                	sw	ra,12(sp)
1c009940:	c422                	sw	s0,8(sp)
1c009942:	8ddfe0ef          	jal	ra,1c00821e <pos_fll_init>
1c009946:	8526                	mv	a0,s1
1c009948:	35e5                	jal	1c009830 <alloc_init_l1>
1c00994a:	04048413          	addi	s0,s1,64
1c00994e:	00201737          	lui	a4,0x201
1c009952:	40070713          	addi	a4,a4,1024 # 201400 <__l1_heap_size+0x1f1408>
1c009956:	045a                	slli	s0,s0,0x16
1c009958:	56fd                	li	a3,-1
1c00995a:	f14027f3          	csrr	a5,mhartid
1c00995e:	00d46723          	p.sw	a3,a4(s0)
1c009962:	ca5797b3          	p.extractu	a5,a5,5,5
1c009966:	477d                	li	a4,31
1c009968:	00e78f63          	beq	a5,a4,1c009986 <cluster_start+0x58>
1c00996c:	002047b7          	lui	a5,0x204
1c009970:	00070737          	lui	a4,0x70
1c009974:	c798                	sw	a4,8(a5)
1c009976:	0ff00713          	li	a4,255
1c00997a:	20078793          	addi	a5,a5,512 # 204200 <__l1_heap_size+0x1f4208>
1c00997e:	00e7a023          	sw	a4,0(a5)
1c009982:	00e7a623          	sw	a4,12(a5)
1c009986:	8526                	mv	a0,s1
1c009988:	3565                	jal	1c009830 <alloc_init_l1>
1c00998a:	6591                	lui	a1,0x4
1c00998c:	8526                	mv	a0,s1
1c00998e:	35d1                	jal	1c009852 <pi_l1_malloc>
1c009990:	100007b7          	lui	a5,0x10000
1c009994:	00a7a223          	sw	a0,4(a5) # 10000004 <cluster_stacks>
1c009998:	c12d                	beqz	a0,1c0099fa <cluster_start+0xcc>
1c00999a:	1c001737          	lui	a4,0x1c001
1c00999e:	4685                	li	a3,1
1c0099a0:	86d72c23          	sw	a3,-1928(a4) # 1c000878 <cluster_running>
1c0099a4:	002007b7          	lui	a5,0x200
1c0099a8:	1c008737          	lui	a4,0x1c008
1c0099ac:	08070713          	addi	a4,a4,128 # 1c008080 <_start>
1c0099b0:	04078693          	addi	a3,a5,64 # 200040 <__l1_heap_size+0x1f0048>
1c0099b4:	00e466a3          	p.sw	a4,a3(s0)
1c0099b8:	04478693          	addi	a3,a5,68
1c0099bc:	00e466a3          	p.sw	a4,a3(s0)
1c0099c0:	04878693          	addi	a3,a5,72
1c0099c4:	00e466a3          	p.sw	a4,a3(s0)
1c0099c8:	04c78693          	addi	a3,a5,76
1c0099cc:	00e466a3          	p.sw	a4,a3(s0)
1c0099d0:	05078693          	addi	a3,a5,80
1c0099d4:	00e466a3          	p.sw	a4,a3(s0)
1c0099d8:	05478693          	addi	a3,a5,84
1c0099dc:	00e466a3          	p.sw	a4,a3(s0)
1c0099e0:	05878693          	addi	a3,a5,88
1c0099e4:	00e466a3          	p.sw	a4,a3(s0)
1c0099e8:	05c78693          	addi	a3,a5,92
1c0099ec:	00e466a3          	p.sw	a4,a3(s0)
1c0099f0:	07a1                	addi	a5,a5,8
1c0099f2:	0ff00713          	li	a4,255
1c0099f6:	00e467a3          	p.sw	a4,a5(s0)
1c0099fa:	40b2                	lw	ra,12(sp)
1c0099fc:	4422                	lw	s0,8(sp)
1c0099fe:	4492                	lw	s1,4(sp)
1c009a00:	0141                	addi	sp,sp,16
1c009a02:	8082                	ret

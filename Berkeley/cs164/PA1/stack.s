#ANN(COOLCLASS, "Object", "_no_class")
#ANN(COOLMETHOD, "Object", "abort", "Object")
#ANN(COOLMETHOD, "Object", "type_name", "String")
#ANN(COOLMETHOD, "Object", "copy", "SELF_TYPE")
#ANN(COOLCLASS, "String", "Object", "Int", "_prim_slot")
#ANN(COOLMETHOD, "String", "length", "Int")
#ANN(COOLMETHOD, "String", "concat", "String", "String")
#ANN(COOLMETHOD, "String", "substr", "Int", "Int", "String")
#ANN(COOLCLASS, "Bool", "Object", "_prim_slot")
#ANN(COOLCLASS, "Int", "Object", "_prim_slot")
#ANN(COOLCLASS, "IO", "Object")
#ANN(COOLMETHOD, "IO", "out_string", "String", "SELF_TYPE")
#ANN(COOLMETHOD, "IO", "out_int", "Int", "SELF_TYPE")
#ANN(COOLMETHOD, "IO", "in_string", "String")
#ANN(COOLMETHOD, "IO", "in_int", "Int")
#ANN(COOLCLASS, "StackCommand","IO", "String")
  #ANN(COOLMETHOD, "StackCommand", "name", "String")
  #ANN(COOLMETHOD, "StackCommand", "show", "Object")
  #ANN(COOLMETHOD, "StackCommand", "init", "String", "SELF_TYPE")
  #ANN(COOLMETHOD, "StackCommand", "eval_stack", "Stack", "Object")
#ANN(COOLCLASS, "PlusCommand","StackCommand")
  #ANN(COOLMETHOD, "PlusCommand", "c2i", "String", "Int")
  #ANN(COOLMETHOD, "PlusCommand", "a2i_aux", "String", "Int")
  #ANN(COOLMETHOD, "PlusCommand", "i2c", "Int", "String")
  #ANN(COOLMETHOD, "PlusCommand", "i2a_aux", "Int", "String")
  #ANN(COOLMETHOD, "PlusCommand", "eval_stack", "Stack", "Object")
#ANN(COOLCLASS, "SCommand","StackCommand")
  #ANN(COOLMETHOD, "SCommand", "eval_stack", "Stack", "Object")
#ANN(COOLCLASS, "Stack","IO", "StackCommand", "Stack")
  #ANN(COOLMETHOD, "Stack", "head", "StackCommand")
  #ANN(COOLMETHOD, "Stack", "tail", "Stack")
  #ANN(COOLMETHOD, "Stack", "pop", "StackCommand")
  #ANN(COOLMETHOD, "Stack", "push", "StackCommand", "Stack")
  #ANN(COOLMETHOD, "Stack", "init", "StackCommand", "Stack")
  #ANN(COOLMETHOD, "Stack", "init2", "StackCommand", "Stack", "Stack")
#ANN(COOLCLASS, "Main","IO")
  #ANN(COOLMETHOD, "Main", "prompt", "String")
  #ANN(COOLMETHOD, "Main", "print_stack", "Stack", "Object")
  #ANN(COOLMETHOD, "Main", "main", "Object")
#ANN(COOLCLASS, "A2I","Object")
  #ANN(COOLMETHOD, "A2I", "c2i", "String", "Int")
  #ANN(COOLMETHOD, "A2I", "i2c", "Int", "String")
  #ANN(COOLMETHOD, "A2I", "a2i", "String", "Int")
  #ANN(COOLMETHOD, "A2I", "a2i_aux", "String", "Int")
  #ANN(COOLMETHOD, "A2I", "i2a", "Int", "String")
  #ANN(COOLMETHOD, "A2I", "i2a_aux", "Int", "String")
	.data
	.align	2
	.globl	class_nameTab
	.globl	Main_protObj
	.globl	Int_protObj
	.globl	String_protObj
	.globl	bool_const0
	.globl	bool_const1
	.globl	_int_tag
	.globl	_bool_tag
	.globl	_string_tag
	.globl	_max_tag
	.globl	class_objTab
	.globl	class_parentTab
	.globl	class_attrTabTab
	.globl	Object_protObj
	.globl	Object_init
	.globl	Object_attrTab
	.globl	A2I_protObj
	.globl	A2I_init
	.globl	A2I_attrTab
	.globl	String_protObj
	.globl	String_init
	.globl	String_attrTab
	.globl	Bool_protObj
	.globl	Bool_init
	.globl	Bool_attrTab
	.globl	Int_protObj
	.globl	Int_init
	.globl	Int_attrTab
	.globl	IO_protObj
	.globl	IO_init
	.globl	IO_attrTab
	.globl	Main_protObj
	.globl	Main_init
	.globl	Main_attrTab
	.globl	Stack_protObj
	.globl	Stack_init
	.globl	Stack_attrTab
	.globl	StackCommand_protObj
	.globl	StackCommand_init
	.globl	StackCommand_attrTab
	.globl	SCommand_protObj
	.globl	SCommand_init
	.globl	SCommand_attrTab
	.globl	PlusCommand_protObj
	.globl	PlusCommand_init
	.globl	PlusCommand_attrTab
_int_tag:
	.word	7
_bool_tag:
	.word	8
_string_tag:
	.word	9
	.globl	_MemMgr_INITIALIZER
_MemMgr_INITIALIZER:
	.word	_NoGC_Init
	.globl	_MemMgr_COLLECTOR
_MemMgr_COLLECTOR:
	.word	_NoGC_Collect
	.globl	_MemMgr_TEST
_MemMgr_TEST:
	.word	0
	.word	-1
str_const32:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"A2I"
	.byte	0	
	.align	2
	.word	-1
str_const31:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"String"
	.byte	0	
	.align	2
	.word	-1
str_const30:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Bool"
	.byte	0	
	.align	2
	.word	-1
str_const29:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const3
	.ascii	"Int"
	.byte	0	
	.align	2
	.word	-1
str_const28:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const4
	.ascii	"Main"
	.byte	0	
	.align	2
	.word	-1
str_const27:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const5
	.ascii	"Stack"
	.byte	0	
	.align	2
	.word	-1
str_const26:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"SCommand"
	.byte	0	
	.align	2
	.word	-1
str_const25:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const11
	.ascii	"PlusCommand"
	.byte	0	
	.align	2
	.word	-1
str_const24:
	.word	9
	.word	8
	.word	String_dispTab
	.word	int_const12
	.ascii	"StackCommand"
	.byte	0	
	.align	2
	.word	-1
str_const23:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const2
	.ascii	"IO"
	.byte	0	
	.align	2
	.word	-1
str_const22:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const6
	.ascii	"Object"
	.byte	0	
	.align	2
	.word	-1
str_const21:
	.word	9
	.word	8
	.word	String_dispTab
	.word	int_const13
	.ascii	"<basic class>"
	.byte	0	
	.align	2
	.word	-1
str_const20:
	.word	9
	.word	6
	.word	String_dispTab
	.word	int_const7
	.ascii	"atoi.cl"
	.byte	0	
	.align	2
	.word	-1
str_const19:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"-"
	.byte	0	
	.align	2
	.word	-1
str_const18:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"e"
	.byte	0	
	.align	2
	.word	-1
str_const17:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"d"
	.byte	0	
	.align	2
	.word	-1
str_const16:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"s"
	.byte	0	
	.align	2
	.word	-1
str_const15:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"+"
	.byte	0	
	.align	2
	.word	-1
str_const14:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"x"
	.byte	0	
	.align	2
	.word	-1
str_const13:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"\n"
	.byte	0	
	.align	2
	.word	-1
str_const12:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	">"
	.byte	0	
	.align	2
	.word	-1
str_const11:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"9"
	.byte	0	
	.align	2
	.word	-1
str_const10:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"8"
	.byte	0	
	.align	2
	.word	-1
str_const9:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"7"
	.byte	0	
	.align	2
	.word	-1
str_const8:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"6"
	.byte	0	
	.align	2
	.word	-1
str_const7:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"5"
	.byte	0	
	.align	2
	.word	-1
str_const6:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"4"
	.byte	0	
	.align	2
	.word	-1
str_const5:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"3"
	.byte	0	
	.align	2
	.word	-1
str_const4:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"2"
	.byte	0	
	.align	2
	.word	-1
str_const3:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"1"
	.byte	0	
	.align	2
	.word	-1
str_const2:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const1
	.ascii	"0"
	.byte	0	
	.align	2
	.word	-1
str_const1:
	.word	9
	.word	7
	.word	String_dispTab
	.word	int_const8
	.ascii	"stack.cl"
	.byte	0	
	.align	2
	.word	-1
str_const0:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.byte	0	
	.align	2
	.word	-1
int_const13:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	13
	.word	-1
int_const12:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	12
	.word	-1
int_const11:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	11
	.word	-1
int_const10:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	10
	.word	-1
int_const9:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	9
	.word	-1
int_const8:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	8
	.word	-1
int_const7:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	7
	.word	-1
int_const6:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	6
	.word	-1
int_const5:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	5
	.word	-1
int_const4:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	4
	.word	-1
int_const3:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	3
	.word	-1
int_const2:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	2
	.word	-1
int_const1:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	1
	.word	-1
int_const0:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
bool_const0:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
bool_const1:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	1
class_nameTab:
	.word	str_const22
	.word	str_const23
	.word	str_const24
	.word	str_const25
	.word	str_const26
	.word	str_const27
	.word	str_const28
	.word	str_const29
	.word	str_const30
	.word	str_const31
	.word	str_const32
class_objTab:
	.word	Object_protObj
	.word	Object_init
	.word	IO_protObj
	.word	IO_init
	.word	StackCommand_protObj
	.word	StackCommand_init
	.word	PlusCommand_protObj
	.word	PlusCommand_init
	.word	SCommand_protObj
	.word	SCommand_init
	.word	Stack_protObj
	.word	Stack_init
	.word	Main_protObj
	.word	Main_init
	.word	Int_protObj
	.word	Int_init
	.word	Bool_protObj
	.word	Bool_init
	.word	String_protObj
	.word	String_init
	.word	A2I_protObj
	.word	A2I_init
_max_tag:
	.word	10
class_parentTab:
	.word	-2
	.word	0
	.word	1
	.word	2
	.word	2
	.word	1
	.word	1
	.word	0
	.word	0
	.word	0
	.word	0
class_attrTabTab:
	.word	Object_attrTab
	.word	IO_attrTab
	.word	StackCommand_attrTab
	.word	PlusCommand_attrTab
	.word	SCommand_attrTab
	.word	Stack_attrTab
	.word	Main_attrTab
	.word	Int_attrTab
	.word	Bool_attrTab
	.word	String_attrTab
	.word	A2I_attrTab
Object_attrTab:
A2I_attrTab:
String_attrTab:
	.word	7
	.word	-2
Bool_attrTab:
	.word	-2
Int_attrTab:
	.word	-2
IO_attrTab:
Main_attrTab:
Stack_attrTab:
	.word	2
	.word	5
StackCommand_attrTab:
	.word	9
SCommand_attrTab:
	.word	9
PlusCommand_attrTab:
	.word	9
Object_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
A2I_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	A2I.c2i
	.word	A2I.i2c
	.word	A2I.a2i
	.word	A2I.a2i_aux
	.word	A2I.i2a
	.word	A2I.i2a_aux
String_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	String.length
	.word	String.concat
	.word	String.substr
Bool_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
Int_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
IO_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
Main_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Main.prompt
	.word	Main.print_stack
	.word	Main.main
Stack_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	Stack.head
	.word	Stack.tail
	.word	Stack.pop
	.word	Stack.push
	.word	Stack.init
	.word	Stack.init2
StackCommand_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	StackCommand.name
	.word	StackCommand.show
	.word	StackCommand.init
	.word	StackCommand.eval_stack
SCommand_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	StackCommand.name
	.word	StackCommand.show
	.word	StackCommand.init
	.word	SCommand.eval_stack
PlusCommand_dispTab:
	.word	Object.abort
	.word	Object.type_name
	.word	Object.copy
	.word	IO.out_string
	.word	IO.out_int
	.word	IO.in_string
	.word	IO.in_int
	.word	StackCommand.name
	.word	StackCommand.show
	.word	StackCommand.init
	.word	PlusCommand.eval_stack
	.word	PlusCommand.c2i
	.word	PlusCommand.a2i_aux
	.word	PlusCommand.i2c
	.word	PlusCommand.i2a_aux
	.word	-1
Object_protObj:
	.word	0
	.word	3
	.word	Object_dispTab
	.word	-1
A2I_protObj:
	.word	10
	.word	3
	.word	A2I_dispTab
	.word	-1
String_protObj:
	.word	9
	.word	5
	.word	String_dispTab
	.word	int_const0
	.word	0
	.word	-1
Bool_protObj:
	.word	8
	.word	4
	.word	Bool_dispTab
	.word	0
	.word	-1
Int_protObj:
	.word	7
	.word	4
	.word	Int_dispTab
	.word	0
	.word	-1
IO_protObj:
	.word	1
	.word	3
	.word	IO_dispTab
	.word	-1
Main_protObj:
	.word	6
	.word	3
	.word	Main_dispTab
	.word	-1
Stack_protObj:
	.word	5
	.word	5
	.word	Stack_dispTab
	.word	0
	.word	0
	.word	-1
StackCommand_protObj:
	.word	2
	.word	4
	.word	StackCommand_dispTab
	.word	str_const0
	.word	-1
SCommand_protObj:
	.word	4
	.word	4
	.word	SCommand_dispTab
	.word	str_const0
	.word	-1
PlusCommand_protObj:
	.word	3
	.word	4
	.word	PlusCommand_dispTab
	.word	str_const0
	.globl	heap_start
heap_start:
	.word	0
	.text
	.globl	Main_init
	.globl	Int_init
	.globl	String_init
	.globl	Bool_init
	.globl	Main.main
Object_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A2I_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
String_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Bool_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Int_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
IO_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	Object_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
StackCommand_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	IO_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
SCommand_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	StackCommand_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
PlusCommand_init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	jal	StackCommand_init
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
A2I.c2i:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$s1 8($fp)
	la	$t2 str_const2
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label2
	la	$a1 bool_const0
	jal	equality_test
label2:
	lw	$t1 12($a0)
	beqz	$t1 label0
	la	$a0 int_const0
	b	label1
label0:
	lw	$s1 8($fp)
	la	$t2 str_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label5
	la	$a1 bool_const0
	jal	equality_test
label5:
	lw	$t1 12($a0)
	beqz	$t1 label3
	la	$a0 int_const1
	b	label4
label3:
	lw	$s1 8($fp)
	la	$t2 str_const4
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label8
	la	$a1 bool_const0
	jal	equality_test
label8:
	lw	$t1 12($a0)
	beqz	$t1 label6
	la	$a0 int_const2
	b	label7
label6:
	lw	$s1 8($fp)
	la	$t2 str_const5
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label11
	la	$a1 bool_const0
	jal	equality_test
label11:
	lw	$t1 12($a0)
	beqz	$t1 label9
	la	$a0 int_const3
	b	label10
label9:
	lw	$s1 8($fp)
	la	$t2 str_const6
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label14
	la	$a1 bool_const0
	jal	equality_test
label14:
	lw	$t1 12($a0)
	beqz	$t1 label12
	la	$a0 int_const4
	b	label13
label12:
	lw	$s1 8($fp)
	la	$t2 str_const7
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label17
	la	$a1 bool_const0
	jal	equality_test
label17:
	lw	$t1 12($a0)
	beqz	$t1 label15
	la	$a0 int_const5
	b	label16
label15:
	lw	$s1 8($fp)
	la	$t2 str_const8
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label20
	la	$a1 bool_const0
	jal	equality_test
label20:
	lw	$t1 12($a0)
	beqz	$t1 label18
	la	$a0 int_const6
	b	label19
label18:
	lw	$s1 8($fp)
	la	$t2 str_const9
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label23
	la	$a1 bool_const0
	jal	equality_test
label23:
	lw	$t1 12($a0)
	beqz	$t1 label21
	la	$a0 int_const7
	b	label22
label21:
	lw	$s1 8($fp)
	la	$t2 str_const10
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label26
	la	$a1 bool_const0
	jal	equality_test
label26:
	lw	$t1 12($a0)
	beqz	$t1 label24
	la	$a0 int_const8
	b	label25
label24:
	lw	$s1 8($fp)
	la	$t2 str_const11
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label29
	la	$a1 bool_const0
	jal	equality_test
label29:
	lw	$t1 12($a0)
	beqz	$t1 label27
	la	$a0 int_const9
	b	label28
label27:
	move	$a0 $s0
	bne	$a0 $zero label30
	la	$a0 str_const20
	li	$t1 26
	jal	_dispatch_abort
label30:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 int_const0
label28:
label25:
label22:
label19:
label16:
label13:
label10:
label7:
label4:
label1:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
A2I.i2c:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$s1 8($fp)
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label33
	la	$a1 bool_const0
	jal	equality_test
label33:
	lw	$t1 12($a0)
	beqz	$t1 label31
	la	$a0 str_const2
	b	label32
label31:
	lw	$s1 8($fp)
	la	$t2 int_const1
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label36
	la	$a1 bool_const0
	jal	equality_test
label36:
	lw	$t1 12($a0)
	beqz	$t1 label34
	la	$a0 str_const3
	b	label35
label34:
	lw	$s1 8($fp)
	la	$t2 int_const2
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label39
	la	$a1 bool_const0
	jal	equality_test
label39:
	lw	$t1 12($a0)
	beqz	$t1 label37
	la	$a0 str_const4
	b	label38
label37:
	lw	$s1 8($fp)
	la	$t2 int_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label42
	la	$a1 bool_const0
	jal	equality_test
label42:
	lw	$t1 12($a0)
	beqz	$t1 label40
	la	$a0 str_const5
	b	label41
label40:
	lw	$s1 8($fp)
	la	$t2 int_const4
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label45
	la	$a1 bool_const0
	jal	equality_test
label45:
	lw	$t1 12($a0)
	beqz	$t1 label43
	la	$a0 str_const6
	b	label44
label43:
	lw	$s1 8($fp)
	la	$t2 int_const5
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label48
	la	$a1 bool_const0
	jal	equality_test
label48:
	lw	$t1 12($a0)
	beqz	$t1 label46
	la	$a0 str_const7
	b	label47
label46:
	lw	$s1 8($fp)
	la	$t2 int_const6
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label51
	la	$a1 bool_const0
	jal	equality_test
label51:
	lw	$t1 12($a0)
	beqz	$t1 label49
	la	$a0 str_const8
	b	label50
label49:
	lw	$s1 8($fp)
	la	$t2 int_const7
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label54
	la	$a1 bool_const0
	jal	equality_test
label54:
	lw	$t1 12($a0)
	beqz	$t1 label52
	la	$a0 str_const9
	b	label53
label52:
	lw	$s1 8($fp)
	la	$t2 int_const8
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label57
	la	$a1 bool_const0
	jal	equality_test
label57:
	lw	$t1 12($a0)
	beqz	$t1 label55
	la	$a0 str_const10
	b	label56
label55:
	lw	$s1 8($fp)
	la	$t2 int_const9
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label60
	la	$a1 bool_const0
	jal	equality_test
label60:
	lw	$t1 12($a0)
	beqz	$t1 label58
	la	$a0 str_const11
	b	label59
label58:
	move	$a0 $s0
	bne	$a0 $zero label61
	la	$a0 str_const20
	li	$t1 44
	jal	_dispatch_abort
label61:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 str_const0
label59:
label56:
label53:
label50:
label47:
label44:
label41:
label38:
label35:
label32:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
A2I.a2i:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$a0 8($fp)
	bne	$a0 $zero label65
	la	$a0 str_const20
	li	$t1 57
	jal	_dispatch_abort
label65:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label64
	la	$a1 bool_const0
	jal	equality_test
label64:
	lw	$t1 12($a0)
	beqz	$t1 label62
	la	$a0 int_const0
	b	label63
label62:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label69
	la	$a0 str_const20
	li	$t1 58
	jal	_dispatch_abort
label69:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 str_const19
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label68
	la	$a1 bool_const0
	jal	equality_test
label68:
	lw	$t1 12($a0)
	beqz	$t1 label66
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label70
	la	$a0 str_const20
	li	$t1 58
	jal	_dispatch_abort
label70:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $a0
	la	$a0 int_const1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label71
	la	$a0 str_const20
	li	$t1 58
	jal	_dispatch_abort
label71:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label72
	la	$a0 str_const20
	li	$t1 58
	jal	_dispatch_abort
label72:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	b	label67
label66:
	la	$a0 int_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label76
	la	$a0 str_const20
	li	$t1 59
	jal	_dispatch_abort
label76:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	move	$s1 $a0
	la	$t2 str_const15
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label75
	la	$a1 bool_const0
	jal	equality_test
label75:
	lw	$t1 12($a0)
	beqz	$t1 label73
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label77
	la	$a0 str_const20
	li	$t1 59
	jal	_dispatch_abort
label77:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s1 $a0
	la	$a0 int_const1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label78
	la	$a0 str_const20
	li	$t1 59
	jal	_dispatch_abort
label78:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label79
	la	$a0 str_const20
	li	$t1 59
	jal	_dispatch_abort
label79:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
	b	label74
label73:
	lw	$a0 8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label80
	la	$a0 str_const20
	li	$t1 60
	jal	_dispatch_abort
label80:
	lw	$t1 8($a0)
	lw	$t1 24($t1)
	jalr		$t1
label74:
label67:
label63:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
A2I.a2i_aux:
	addiu	$sp $sp -44
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 16($fp)
	sw	$s2 20($fp)
	sw	$s3 24($fp)
	sw	$s4 28($fp)
	la	$s1 int_const0
	lw	$a0 32($fp)
	bne	$a0 $zero label81
	la	$a0 str_const20
	li	$t1 71
	jal	_dispatch_abort
label81:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s2 $a0
	la	$s3 int_const0
label82:
	move	$s4 $s3
	lw	$t1 12($s4)
	lw	$t2 12($s2)
	la	$a0 bool_const1
	blt	$t1 $t2 label84
	la	$a0 bool_const0
label84:
	lw	$t1 12($a0)
	beq	$t1 $zero label83
	move	$s4 $s1
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s4 $a0
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($fp)
	bne	$a0 $zero label85
	la	$a0 str_const20
	li	$t1 75
	jal	_dispatch_abort
label85:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label86
	la	$a0 str_const20
	li	$t1 75
	jal	_dispatch_abort
label86:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	move	$s4 $s3
	la	$a0 int_const1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	b	label82
label83:
	move	$a0 $zero
	move	$a0 $s1
	lw	$s1 16($fp)
	lw	$s2 20($fp)
	lw	$s3 24($fp)
	lw	$s4 28($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 48
	jr	$ra	
A2I.i2a:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$s1 8($fp)
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label89
	la	$a1 bool_const0
	jal	equality_test
label89:
	lw	$t1 12($a0)
	beqz	$t1 label87
	la	$a0 str_const2
	b	label88
label87:
	la	$s1 int_const0
	lw	$a0 8($fp)
	lw	$t1 12($s1)
	lw	$t2 12($a0)
	la	$a0 bool_const1
	blt	$t1 $t2 label92
	la	$a0 bool_const0
label92:
	lw	$t1 12($a0)
	beqz	$t1 label90
	lw	$a0 8($fp)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label93
	la	$a0 str_const20
	li	$t1 92
	jal	_dispatch_abort
label93:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	b	label91
label90:
	lw	$s1 8($fp)
	la	$a0 int_const1
	jal	Object.copy
	lw	$t1 12($a0)
	neg	$t1 $t1
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label94
	la	$a0 str_const20
	li	$t1 93
	jal	_dispatch_abort
label94:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 str_const19
	bne	$a0 $zero label95
	la	$a0 str_const20
	li	$t1 93
	jal	_dispatch_abort
label95:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
label91:
label88:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
A2I.i2a_aux:
	addiu	$sp $sp -36
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 12($fp)
	sw	$s2 16($fp)
	sw	$s3 20($fp)
	lw	$s1 24($fp)
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label98
	la	$a1 bool_const0
	jal	equality_test
label98:
	lw	$t1 12($a0)
	beqz	$t1 label96
	la	$a0 str_const0
	b	label97
label96:
	lw	$s1 24($fp)
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	div	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$s2 24($fp)
	move	$s3 $s1
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s2)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label99
	la	$a0 str_const20
	li	$t1 103
	jal	_dispatch_abort
label99:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label100
	la	$a0 str_const20
	li	$t1 103
	jal	_dispatch_abort
label100:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label101
	la	$a0 str_const20
	li	$t1 103
	jal	_dispatch_abort
label101:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
label97:
	lw	$s1 12($fp)
	lw	$s2 16($fp)
	lw	$s3 20($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 40
	jr	$ra	
Main.prompt:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	la	$a0 str_const12
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label102
	la	$a0 str_const1
	li	$t1 156
	jal	_dispatch_abort
label102:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$a0 $s0
	bne	$a0 $zero label103
	la	$a0 str_const1
	li	$t1 157
	jal	_dispatch_abort
label103:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Main.print_stack:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$a0 8($fp)
	la	$s1 bool_const1
	beqz	$a0 label107
	la	$s1 bool_const0
label107:
	la	$t2 bool_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label106
	la	$a1 bool_const0
	jal	equality_test
label106:
	lw	$t1 12($a0)
	beqz	$t1 label104
	lw	$a0 8($fp)
	bne	$a0 $zero label112
	la	$a0 str_const1
	li	$t1 161
	jal	_dispatch_abort
label112:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	la	$s1 bool_const1
	beqz	$a0 label111
	la	$s1 bool_const0
label111:
	la	$t2 bool_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label110
	la	$a1 bool_const0
	jal	equality_test
label110:
	lw	$t1 12($a0)
	beqz	$t1 label108
	la	$a0 str_const13
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 8($fp)
	bne	$a0 $zero label113
	la	$a0 str_const1
	li	$t1 162
	jal	_dispatch_abort
label113:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	bne	$a0 $zero label114
	la	$a0 str_const1
	li	$t1 162
	jal	_dispatch_abort
label114:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	bne	$a0 $zero label115
	la	$a0 str_const1
	li	$t1 162
	jal	_dispatch_abort
label115:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label116
	la	$a0 str_const1
	li	$t1 162
	jal	_dispatch_abort
label116:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$a0 8($fp)
	bne	$a0 $zero label117
	la	$a0 str_const1
	li	$t1 163
	jal	_dispatch_abort
label117:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label118
	la	$a0 str_const1
	li	$t1 163
	jal	_dispatch_abort
label118:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	b	label109
label108:
	la	$a0 str_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label119
	la	$a0 str_const1
	li	$t1 165
	jal	_dispatch_abort
label119:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label109:
	b	label105
label104:
	la	$a0 str_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label120
	la	$a0 str_const1
	li	$t1 167
	jal	_dispatch_abort
label120:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
label105:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
Main.main:
	addiu	$sp $sp -36
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 12($fp)
	sw	$s2 16($fp)
	sw	$s3 20($fp)
	la	$s1 str_const0
	la	$a0 Stack_protObj
	jal	Object.copy
	jal	Stack_init
	move	$s2 $a0
label121:
	move	$a0 $s0
	bne	$a0 $zero label125
	la	$a0 str_const1
	li	$t1 174
	jal	_dispatch_abort
label125:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	move	$s1 $a0
	move	$s3 $a0
	la	$t2 str_const14
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label124
	la	$a1 bool_const0
	jal	equality_test
label124:
	move	$s3 $a0
	la	$t2 bool_const0
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label123
	la	$a1 bool_const0
	jal	equality_test
label123:
	lw	$t1 12($a0)
	beq	$t1 $zero label122
	move	$s3 $s1
	la	$t2 str_const15
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label128
	la	$a1 bool_const0
	jal	equality_test
label128:
	lw	$t1 12($a0)
	beqz	$t1 label126
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	la	$a0 PlusCommand_protObj
	jal	Object.copy
	jal	PlusCommand_init
	bne	$a0 $zero label129
	la	$a0 str_const1
	li	$t1 176
	jal	_dispatch_abort
label129:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s2
	bne	$a0 $zero label130
	la	$a0 str_const1
	li	$t1 176
	jal	_dispatch_abort
label130:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	b	label127
label126:
	move	$s3 $s1
	la	$t2 str_const16
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label133
	la	$a1 bool_const0
	jal	equality_test
label133:
	lw	$t1 12($a0)
	beqz	$t1 label131
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	la	$a0 SCommand_protObj
	jal	Object.copy
	jal	SCommand_init
	bne	$a0 $zero label134
	la	$a0 str_const1
	li	$t1 177
	jal	_dispatch_abort
label134:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s2
	bne	$a0 $zero label135
	la	$a0 str_const1
	li	$t1 177
	jal	_dispatch_abort
label135:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	b	label132
label131:
	move	$s3 $s1
	la	$t2 str_const17
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label138
	la	$a1 bool_const0
	jal	equality_test
label138:
	lw	$t1 12($a0)
	beqz	$t1 label136
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label139
	la	$a0 str_const1
	li	$t1 178
	jal	_dispatch_abort
label139:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	b	label137
label136:
	move	$s3 $s1
	la	$t2 str_const18
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label142
	la	$a1 bool_const0
	jal	equality_test
label142:
	lw	$t1 12($a0)
	beqz	$t1 label140
	move	$a0 $s2
	bne	$a0 $zero label147
	la	$a0 str_const1
	li	$t1 180
	jal	_dispatch_abort
label147:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	la	$s3 bool_const1
	beqz	$a0 label146
	la	$s3 bool_const0
label146:
	la	$t2 bool_const0
	move	$t1 $s3
	la	$a0 bool_const1
	beq	$t1 $t2 label145
	la	$a1 bool_const0
	jal	equality_test
label145:
	lw	$t1 12($a0)
	beqz	$t1 label143
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s2
	bne	$a0 $zero label148
	la	$a0 str_const1
	li	$t1 180
	jal	_dispatch_abort
label148:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	bne	$a0 $zero label149
	la	$a0 str_const1
	li	$t1 180
	jal	_dispatch_abort
label149:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	b	label144
label143:
	la	$a0 int_const0
label144:
	b	label141
label140:
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	la	$a0 StackCommand_protObj
	jal	Object.copy
	jal	StackCommand_init
	bne	$a0 $zero label150
	la	$a0 str_const1
	li	$t1 181
	jal	_dispatch_abort
label150:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s2
	bne	$a0 $zero label151
	la	$a0 str_const1
	li	$t1 181
	jal	_dispatch_abort
label151:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
label141:
label137:
label132:
label127:
	b	label121
label122:
	move	$a0 $zero
	lw	$s1 12($fp)
	lw	$s2 16($fp)
	lw	$s3 20($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 36
	jr	$ra	
Stack.head:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 12($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.tail:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 16($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
Stack.pop:
	addiu	$sp $sp -28
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 8($fp)
	sw	$s2 12($fp)
	move	$a0 $s0
	bne	$a0 $zero label152
	la	$a0 str_const1
	li	$t1 118
	jal	_dispatch_abort
label152:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	move	$s1 $a0
	move	$a0 $s0
	bne	$a0 $zero label156
	la	$a0 str_const1
	li	$t1 120
	jal	_dispatch_abort
label156:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label155
	la	$a0 bool_const0
label155:
	lw	$t1 12($a0)
	beqz	$t1 label153
	move	$s2 $zero
	sw	$s2 12($s0)
	move	$a0 $s2
	b	label154
label153:
	move	$a0 $s0
	bne	$a0 $zero label157
	la	$a0 str_const1
	li	$t1 124
	jal	_dispatch_abort
label157:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label158
	la	$a0 str_const1
	li	$t1 124
	jal	_dispatch_abort
label158:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 12($s0)
	move	$a0 $s0
	bne	$a0 $zero label159
	la	$a0 str_const1
	li	$t1 125
	jal	_dispatch_abort
label159:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label160
	la	$a0 str_const1
	li	$t1 125
	jal	_dispatch_abort
label160:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	sw	$a0 16($s0)
label154:
	move	$a0 $s1
	lw	$s1 8($fp)
	lw	$s2 12($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 28
	jr	$ra	
Stack.push:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	move	$a0 $s0
	bne	$a0 $zero label164
	la	$a0 str_const1
	li	$t1 131
	jal	_dispatch_abort
label164:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label163
	la	$a0 bool_const0
label163:
	lw	$t1 12($a0)
	beqz	$t1 label161
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	b	label162
label161:
	move	$a0 $s0
	bne	$a0 $zero label168
	la	$a0 str_const1
	li	$t1 134
	jal	_dispatch_abort
label168:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	move	$t1 $a0
	la	$a0 bool_const1
	beqz	$t1 label167
	la	$a0 bool_const0
label167:
	lw	$t1 12($a0)
	beqz	$t1 label165
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 Stack_protObj
	jal	Object.copy
	jal	Stack_init
	bne	$a0 $zero label169
	la	$a0 str_const1
	li	$t1 135
	jal	_dispatch_abort
label169:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	sw	$a0 16($s0)
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	b	label166
label165:
	move	$a0 $s0
	bne	$a0 $zero label170
	la	$a0 str_const1
	li	$t1 138
	jal	_dispatch_abort
label170:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label171
	la	$a0 str_const1
	li	$t1 138
	jal	_dispatch_abort
label171:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label172
	la	$a0 str_const1
	li	$t1 138
	jal	_dispatch_abort
label172:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	sw	$a0 16($s0)
	lw	$a0 0($fp)
	sw	$a0 12($s0)
label166:
label162:
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Stack.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
Stack.init2:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 4($fp)
	sw	$a0 12($s0)
	lw	$a0 0($fp)
	sw	$a0 16($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 20
	jr	$ra	
StackCommand.name:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 12($s0)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
StackCommand.show:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 12($s0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label173
	la	$a0 str_const1
	li	$t1 14
	jal	_dispatch_abort
label173:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 12
	jr	$ra	
StackCommand.init:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	lw	$a0 0($fp)
	sw	$a0 12($s0)
	move	$a0 $s0
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
StackCommand.eval_stack:
	addiu	$sp $sp -12
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	la	$a0 str_const0
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label174
	la	$a0 str_const1
	li	$t1 20
	jal	_dispatch_abort
label174:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 16
	jr	$ra	
SCommand.eval_stack:
	addiu	$sp $sp -28
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 8($fp)
	sw	$s2 12($fp)
	move	$s1 $zero
	move	$s2 $zero
	lw	$a0 16($fp)
	bne	$a0 $zero label175
	la	$a0 str_const1
	li	$t1 100
	jal	_dispatch_abort
label175:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	lw	$a0 16($fp)
	bne	$a0 $zero label176
	la	$a0 str_const1
	li	$t1 101
	jal	_dispatch_abort
label176:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$a0 16($fp)
	bne	$a0 $zero label177
	la	$a0 str_const1
	li	$t1 102
	jal	_dispatch_abort
label177:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	move	$s2 $a0
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($fp)
	bne	$a0 $zero label178
	la	$a0 str_const1
	li	$t1 103
	jal	_dispatch_abort
label178:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	sw	$s2 0($sp)
	addiu	$sp $sp -4
	lw	$a0 16($fp)
	bne	$a0 $zero label179
	la	$a0 str_const1
	li	$t1 104
	jal	_dispatch_abort
label179:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$s1 8($fp)
	lw	$s2 12($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 32
	jr	$ra	
PlusCommand.c2i:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$s1 8($fp)
	la	$t2 str_const2
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label182
	la	$a1 bool_const0
	jal	equality_test
label182:
	lw	$t1 12($a0)
	beqz	$t1 label180
	la	$a0 int_const0
	b	label181
label180:
	lw	$s1 8($fp)
	la	$t2 str_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label185
	la	$a1 bool_const0
	jal	equality_test
label185:
	lw	$t1 12($a0)
	beqz	$t1 label183
	la	$a0 int_const1
	b	label184
label183:
	lw	$s1 8($fp)
	la	$t2 str_const4
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label188
	la	$a1 bool_const0
	jal	equality_test
label188:
	lw	$t1 12($a0)
	beqz	$t1 label186
	la	$a0 int_const2
	b	label187
label186:
	lw	$s1 8($fp)
	la	$t2 str_const5
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label191
	la	$a1 bool_const0
	jal	equality_test
label191:
	lw	$t1 12($a0)
	beqz	$t1 label189
	la	$a0 int_const3
	b	label190
label189:
	lw	$s1 8($fp)
	la	$t2 str_const6
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label194
	la	$a1 bool_const0
	jal	equality_test
label194:
	lw	$t1 12($a0)
	beqz	$t1 label192
	la	$a0 int_const4
	b	label193
label192:
	lw	$s1 8($fp)
	la	$t2 str_const7
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label197
	la	$a1 bool_const0
	jal	equality_test
label197:
	lw	$t1 12($a0)
	beqz	$t1 label195
	la	$a0 int_const5
	b	label196
label195:
	lw	$s1 8($fp)
	la	$t2 str_const8
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label200
	la	$a1 bool_const0
	jal	equality_test
label200:
	lw	$t1 12($a0)
	beqz	$t1 label198
	la	$a0 int_const6
	b	label199
label198:
	lw	$s1 8($fp)
	la	$t2 str_const9
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label203
	la	$a1 bool_const0
	jal	equality_test
label203:
	lw	$t1 12($a0)
	beqz	$t1 label201
	la	$a0 int_const7
	b	label202
label201:
	lw	$s1 8($fp)
	la	$t2 str_const10
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label206
	la	$a1 bool_const0
	jal	equality_test
label206:
	lw	$t1 12($a0)
	beqz	$t1 label204
	la	$a0 int_const8
	b	label205
label204:
	lw	$s1 8($fp)
	la	$t2 str_const11
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label209
	la	$a1 bool_const0
	jal	equality_test
label209:
	lw	$t1 12($a0)
	beqz	$t1 label207
	la	$a0 int_const9
	b	label208
label207:
	move	$a0 $s0
	bne	$a0 $zero label210
	la	$a0 str_const1
	li	$t1 38
	jal	_dispatch_abort
label210:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 int_const0
label208:
label205:
label202:
label199:
label196:
label193:
label190:
label187:
label184:
label181:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
PlusCommand.a2i_aux:
	addiu	$sp $sp -44
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 16($fp)
	sw	$s2 20($fp)
	sw	$s3 24($fp)
	sw	$s4 28($fp)
	la	$s1 int_const0
	lw	$a0 32($fp)
	bne	$a0 $zero label211
	la	$a0 str_const1
	li	$t1 44
	jal	_dispatch_abort
label211:
	lw	$t1 8($a0)
	lw	$t1 12($t1)
	jalr		$t1
	move	$s2 $a0
	la	$s3 int_const0
label212:
	move	$s4 $s3
	lw	$t1 12($s4)
	lw	$t2 12($s2)
	la	$a0 bool_const1
	blt	$t1 $t2 label214
	la	$a0 bool_const0
label214:
	lw	$t1 12($a0)
	beq	$t1 $zero label213
	move	$s4 $s1
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s4 $a0
	sw	$s3 0($sp)
	addiu	$sp $sp -4
	la	$a0 int_const1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 32($fp)
	bne	$a0 $zero label215
	la	$a0 str_const1
	li	$t1 48
	jal	_dispatch_abort
label215:
	lw	$t1 8($a0)
	lw	$t1 20($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label216
	la	$a0 str_const1
	li	$t1 48
	jal	_dispatch_abort
label216:
	lw	$t1 8($a0)
	lw	$t1 44($t1)
	jalr		$t1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	move	$s4 $s3
	la	$a0 int_const1
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s4)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s3 $a0
	b	label212
label213:
	move	$a0 $zero
	move	$a0 $s1
	lw	$s1 16($fp)
	lw	$s2 20($fp)
	lw	$s3 24($fp)
	lw	$s4 28($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 48
	jr	$ra	
PlusCommand.i2c:
	addiu	$sp $sp -20
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 4($fp)
	lw	$s1 8($fp)
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label219
	la	$a1 bool_const0
	jal	equality_test
label219:
	lw	$t1 12($a0)
	beqz	$t1 label217
	la	$a0 str_const2
	b	label218
label217:
	lw	$s1 8($fp)
	la	$t2 int_const1
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label222
	la	$a1 bool_const0
	jal	equality_test
label222:
	lw	$t1 12($a0)
	beqz	$t1 label220
	la	$a0 str_const3
	b	label221
label220:
	lw	$s1 8($fp)
	la	$t2 int_const2
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label225
	la	$a1 bool_const0
	jal	equality_test
label225:
	lw	$t1 12($a0)
	beqz	$t1 label223
	la	$a0 str_const4
	b	label224
label223:
	lw	$s1 8($fp)
	la	$t2 int_const3
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label228
	la	$a1 bool_const0
	jal	equality_test
label228:
	lw	$t1 12($a0)
	beqz	$t1 label226
	la	$a0 str_const5
	b	label227
label226:
	lw	$s1 8($fp)
	la	$t2 int_const4
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label231
	la	$a1 bool_const0
	jal	equality_test
label231:
	lw	$t1 12($a0)
	beqz	$t1 label229
	la	$a0 str_const6
	b	label230
label229:
	lw	$s1 8($fp)
	la	$t2 int_const5
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label234
	la	$a1 bool_const0
	jal	equality_test
label234:
	lw	$t1 12($a0)
	beqz	$t1 label232
	la	$a0 str_const7
	b	label233
label232:
	lw	$s1 8($fp)
	la	$t2 int_const6
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label237
	la	$a1 bool_const0
	jal	equality_test
label237:
	lw	$t1 12($a0)
	beqz	$t1 label235
	la	$a0 str_const8
	b	label236
label235:
	lw	$s1 8($fp)
	la	$t2 int_const7
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label240
	la	$a1 bool_const0
	jal	equality_test
label240:
	lw	$t1 12($a0)
	beqz	$t1 label238
	la	$a0 str_const9
	b	label239
label238:
	lw	$s1 8($fp)
	la	$t2 int_const8
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label243
	la	$a1 bool_const0
	jal	equality_test
label243:
	lw	$t1 12($a0)
	beqz	$t1 label241
	la	$a0 str_const10
	b	label242
label241:
	lw	$s1 8($fp)
	la	$t2 int_const9
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label246
	la	$a1 bool_const0
	jal	equality_test
label246:
	lw	$t1 12($a0)
	beqz	$t1 label244
	la	$a0 str_const11
	b	label245
label244:
	move	$a0 $s0
	bne	$a0 $zero label247
	la	$a0 str_const1
	li	$t1 70
	jal	_dispatch_abort
label247:
	lw	$t1 8($a0)
	lw	$t1 0($t1)
	jalr		$t1
	la	$a0 str_const0
label245:
label242:
label239:
label236:
label233:
label230:
label227:
label224:
label221:
label218:
	lw	$s1 4($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 24
	jr	$ra	
PlusCommand.i2a_aux:
	addiu	$sp $sp -36
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 12($fp)
	sw	$s2 16($fp)
	sw	$s3 20($fp)
	lw	$s1 24($fp)
	la	$t2 int_const0
	move	$t1 $s1
	la	$a0 bool_const1
	beq	$t1 $t2 label250
	la	$a1 bool_const0
	jal	equality_test
label250:
	lw	$t1 12($a0)
	beqz	$t1 label248
	la	$a0 str_const0
	b	label249
label248:
	lw	$s1 24($fp)
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s1)
	div	$t1 $t1 $t2
	sw	$t1 12($a0)
	move	$s1 $a0
	lw	$s2 24($fp)
	move	$s3 $s1
	la	$a0 int_const10
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	mul	$t1 $t1 $t2
	sw	$t1 12($a0)
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s2)
	sub	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label251
	la	$a0 str_const1
	li	$t1 77
	jal	_dispatch_abort
label251:
	lw	$t1 8($a0)
	lw	$t1 52($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	sw	$s1 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label252
	la	$a0 str_const1
	li	$t1 77
	jal	_dispatch_abort
label252:
	lw	$t1 8($a0)
	lw	$t1 56($t1)
	jalr		$t1
	bne	$a0 $zero label253
	la	$a0 str_const1
	li	$t1 77
	jal	_dispatch_abort
label253:
	lw	$t1 8($a0)
	lw	$t1 16($t1)
	jalr		$t1
label249:
	lw	$s1 12($fp)
	lw	$s2 16($fp)
	lw	$s3 20($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 40
	jr	$ra	
PlusCommand.eval_stack:
	addiu	$sp $sp -36
	sw	$fp 12($sp)
	sw	$s0 8($sp)
	sw	$ra 4($sp)
	addiu	$fp $sp 16
	move	$s0 $a0
	sw	$s1 12($fp)
	sw	$s2 16($fp)
	sw	$s3 20($fp)
	lw	$a0 24($fp)
	bne	$a0 $zero label254
	la	$a0 str_const1
	li	$t1 83
	jal	_dispatch_abort
label254:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label255
	la	$a0 str_const1
	li	$t1 83
	jal	_dispatch_abort
label255:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	bne	$a0 $zero label256
	la	$a0 str_const1
	li	$t1 83
	jal	_dispatch_abort
label256:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label257
	la	$a0 str_const1
	li	$t1 83
	jal	_dispatch_abort
label257:
	lw	$t1 8($a0)
	lw	$t1 48($t1)
	jalr		$t1
	move	$s1 $a0
	lw	$a0 24($fp)
	bne	$a0 $zero label258
	la	$a0 str_const1
	li	$t1 84
	jal	_dispatch_abort
label258:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label259
	la	$a0 str_const1
	li	$t1 84
	jal	_dispatch_abort
label259:
	lw	$t1 8($a0)
	lw	$t1 32($t1)
	jalr		$t1
	bne	$a0 $zero label260
	la	$a0 str_const1
	li	$t1 84
	jal	_dispatch_abort
label260:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	bne	$a0 $zero label261
	la	$a0 str_const1
	li	$t1 84
	jal	_dispatch_abort
label261:
	lw	$t1 8($a0)
	lw	$t1 28($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label262
	la	$a0 str_const1
	li	$t1 84
	jal	_dispatch_abort
label262:
	lw	$t1 8($a0)
	lw	$t1 48($t1)
	jalr		$t1
	move	$s2 $a0
	lw	$a0 24($fp)
	bne	$a0 $zero label263
	la	$a0 str_const1
	li	$t1 86
	jal	_dispatch_abort
label263:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	lw	$a0 24($fp)
	bne	$a0 $zero label264
	la	$a0 str_const1
	li	$t1 87
	jal	_dispatch_abort
label264:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	lw	$a0 24($fp)
	bne	$a0 $zero label265
	la	$a0 str_const1
	li	$t1 88
	jal	_dispatch_abort
label265:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	move	$s3 $s1
	move	$a0 $s2
	jal	Object.copy
	lw	$t2 12($a0)
	lw	$t1 12($s3)
	add	$t1 $t1 $t2
	sw	$t1 12($a0)
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	move	$a0 $s0
	bne	$a0 $zero label266
	la	$a0 str_const1
	li	$t1 89
	jal	_dispatch_abort
label266:
	lw	$t1 8($a0)
	lw	$t1 56($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	la	$a0 StackCommand_protObj
	jal	Object.copy
	jal	StackCommand_init
	bne	$a0 $zero label267
	la	$a0 str_const1
	li	$t1 89
	jal	_dispatch_abort
label267:
	lw	$t1 8($a0)
	lw	$t1 36($t1)
	jalr		$t1
	sw	$a0 0($sp)
	addiu	$sp $sp -4
	lw	$a0 24($fp)
	bne	$a0 $zero label268
	la	$a0 str_const1
	li	$t1 89
	jal	_dispatch_abort
label268:
	lw	$t1 8($a0)
	lw	$t1 40($t1)
	jalr		$t1
	lw	$s1 12($fp)
	lw	$s2 16($fp)
	lw	$s3 20($fp)
	lw	$fp 12($sp)
	lw	$s0 8($sp)
	lw	$ra 4($sp)
	addiu	$sp $sp 40
	jr	$ra	

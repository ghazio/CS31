# Names: Sidhika Tripathee and Ghazi Randhawa
	.text
.global swap
	.type	swap, @function
swap:
	pushl	%ebp                # stack set-up code
	movl	%esp, %ebp
	subl	$16, %esp

    # ADD YOUR CODE IN HERE
    # Use only %eax, %ecx, and %edx if you need registers

  movl 0x8(%ebp),%eax   #moves *x into eax
	movl (%eax), %eax			#puts value of eax into eax (x) deferencing
	movl 0xc(%ebp), %ecx  #moves *y into ecx
	movl (%ecx),%edx				#puts value of ecx into empty register
	movl %eax, (%ecx)       #moves *x into memory address of y


  movl 0x8(%ebp),%eax 
	movl %edx, (%eax)       #copies edx(temp value) to memory address of x


	leave                       # function return code
	ret

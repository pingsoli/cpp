
# Chapter 10 Testing and debugging multithread applications

reviewing code to locate potential bugs  

## Questions to think about when reviewing multithread code
Which data needs to be protected from concurrent access ?  
How do you ensure that the data is protected ?  
Where in the code could other threads be at this time ?  
Which mutexes does this thread hold ?  
Which mutexes might other threads hold ?  
Are there any ordering requirements between the operations done in this thread
and those done in another ? How are those requirements enforced ?  
Is the data loaded by this thread still valid ? Could it have been modified by
other threads ?  
If you assume that another thread could be modifying the data, what would that
mean and how could you ensure that this never happens ?  

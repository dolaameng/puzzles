import random

def countSteps(probab,ladder,snake):
	stepList=[]	
	counter=5000

	cumProbab=[sum(probab[:i+1]) for i,v in enumerate(probab)]

	while(counter>0):
		steps=0
		position=1
		while(position<100):
			throw=random.random()+0.01
			if throw>1.000:
				idx=6
			else:
				diff=min(filter(lambda x:x-throw>0, cumProbab))
				idx=cumProbab.index(diff)
			if position+(idx+1)<=100:
				position=position+(idx+1)
			for l in ladder:
				if position==l[0]:
					position=l[1]
			for s in snake:
				if position==s[0]:
					position=s[1]
			steps+=1
			
		if steps>1000:
			continue
		else:
			counter-=1
			stepList.append(steps)
	return stepList


T=int(raw_input())
for i in range(T):
	probab=map(float,raw_input().strip().split(','))
	Lcnt,Scnt=map(int,raw_input().strip().split(','))
	L=raw_input().strip().split(' ')
	ladder=[tuple(map(int,x.split(','))) for x in L]
	S=raw_input().strip().split(' ')
	snake=[tuple(map(int,x.split(','))) for x in S]
	stepList=countSteps(probab,ladder,snake)
	print int(sum(stepList)/(len(stepList)*1.))
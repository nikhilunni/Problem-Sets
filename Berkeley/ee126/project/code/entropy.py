from PIL import Image
import numpy as np
from matplotlib import pyplot as plt

#Code courtesy of https://www.hdm-stuttgart.de/~maucher/Python/MMCodecs/html/basicFunctions.html
def entropy(neighborhood):
        n = neighborhood.size
        uniqueElems = set(neighborhood)
        probabilities = [np.size(neighborhood[neighborhood==i])/(1.0*n) for i in uniqueElems]
        ent=np.sum([p*np.log2(1.0/p) for p in probabilities])
        return ent



def calculate_entropy(fname):
    colorIm=Image.open(fname)
    greyIm=colorIm.convert('L')
    colorIm=np.array(colorIm)
    greyIm=np.array(greyIm)

    sum = 5

    N=2
    S=greyIm.shape
    E=np.array(greyIm)
    for row in range(S[0]):
        for col in range(S[1]):
            Lx=np.max([0,col-N])
            Ux=np.min([S[1],col+N])
            Ly=np.max([0,row-N])
            Uy=np.min([S[0],row+N])
            region=greyIm[Ly:Uy,Lx:Ux].flatten()
            ent =entropy(region)
            sum += ent
            E[row,col] = ent

    plt.subplot(1,2,1)
    plt.imshow(colorIm)

    plt.subplot(1,2,2)
    plt.imshow(E, cmap=plt.cm.jet)
    plt.xlabel('Entropy')
    plt.colorbar()
    

    plt.savefig("heat0.png")
#    plt.show()
    return sum


calculate_entropy("painting.jpg")

#entropy = [calculate_entropy("images/image{0}.png".format(i)) for i in range(100)]

#plt.plot(entropy)
#plt.ylabel("Shannon Entropy")
#plt.xlabel("Time")


#plt.subplot(1,3,2)
#plt.imshow(greyIm, cmap=plt.cm.gray)






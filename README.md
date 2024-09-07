<img src="https://imgur.com/HIGhzcG.png" alt="logo" width="100"/>

# Oculta
An encryption and authentication library. Provides encryption algorithms and can also also hash and store passwords. The purpose of this library is to setup your own authentication service similar to Cognito that you could spin and configure on your own and adapt to the cloud service of your choise. I was also just curious in implmenting popular Cryptography libraries.

## Dependency   
You need cmake and also you have to download and the mongoose.c and mongoose.h file and make sure to put it in libs/mongoose from this [repo](https://github.com/cesanta/mongoose/).

## Why?
Along with interest I had in cryptography, I also had an interest in creating infastructure for some of my projects on my own. Usually when I have an idea and I want to have a user login system, I user services like Cognito or Firebase. This usually offers some ensurance that your authentication system has security, scalability and flexibility as it those services support Oauth2.0 which can use a variety of different services. There are new services that specify just on authentication services. I felt that I really did not like dealing with hassle of dealing with configuration if I could just do it myself. There is also a cost of using these services after you hit a certain amount of users. This may seem trivial at first, but can amout to a lot and eat away at you later. Most of these services are just software built upon aws. I wanted to try doing this myself.

## Encryption:
- RSA
- AES
The encryption methods had me dive into a lot of math. Most of the math I learned in uni from Math 178, but the implementation took a little more thought. The RSA uses 64 bit integers, while the Simplified AES uses 8 bit integers. For larger bit keys for more standard options like the 256 bit RSA algorithm, I think that needs an custom Integer class to support mathamatical operations. 

### RSA   
Briefiest summary of RSA, generate 2 prime numbers p and q. The product of the 2 primes is equal to the public mod m. Then, create a public key, e, by selecting a numeber between 1 and totient function of n that is also coprime with totient function of n. From the public key, e, solve for the private key d using the extended euclidean algorithm.    
**Generating Prime Numbers**   
A important question that I had to figure out was how to determine how to generate the prime nubmers. The code here is very simple. I generate a large 64 bit number and check if the number passes the Amplified Miller Rabin test. The miller rabin test is a non-deterministic test for prime numbers. There is a chance that it could be wrong, but it is very low. I wonder what a more industry standard apporoach to gernerating prime numbers would be.
```Cpp
int64 generatePrime(){
	//1. Generate Random Number
	//2. Check if it is prime with miller Rabin or fermats prime test
	//3. If not, generate another
	int64 prime = random64bit();
	while(!millerRabinAmplify(prime) || prime < 10000000){
		prime = random64bit();
	}
	return prime;
}
```
### Simplified AES   
I believe this is a very popular public encryption. It is not as popular as the Standard AES, as it does not have as much as steps and not secure enought. This algorithm still has many steps to it that makes it very interesing more detial on this alorithm can be found [here](https://www.rose-hulman.edu/class/ma/holden/Archived_Courses/Math479-0304/lectures/s-aes.pdf). There were many steps. Many of them included Nibble manipulation. This required a lot of bit manipulation.

### Encoding
- base64
Implemented a base64 encoding used by both RSA and AES. 

### Testing
There were tests written for all the modules including the generation of primes, miller rabing, euclidean algorithm, RSA, and AES. I went into this project with a testing first mentality. I believe that these are very important services that need to be secure and work properly. You can run the tests after building the cmake project with:
``` make test ```

# Auth
- sha1 hash   
To build the application the user need to have cmake. Then, you can run:       
```cmake .```   
For the authentication part of the project, the user can specify setting for the password and session cookie throught the command line when running the microservice.   
``` Usage: ./server --password_length <length> --numbers <numbers> --others <others> --capitals <capitals> --token_duration <token_duration> ```   
There are three main endpoints, when the service is running.
1. /api/signup -> Creates user in database after hasing with SHA1 of password.
2. /api/login -> Creates session cookie after it verifies username and password.
3. /home -> Verifies session cookie.
I felt like these were theree main functions that anyone needs to quickly setup an authentcation service. No Oauth2.0 for authentication with other services. Check the examples to see how it is done.

## Future Work   
I think there are many things that an authentication service. I think I could implement Oauth2.0 to have other service work this service like Firebase. I also think that I can implment an encryption service where I add an endpoint that encrypts based up on a set up key.  Make an issue on the [repo](https://github.com/8coolguy/ocultacd) to notify of concerns or ideas if anyone reads this.
# Use an official C++ runtime as a parent image
FROM gcc:latest

# Set the working directory in the container to /app
WORKDIR /app

# Copy the current directory contents into the container at /app
COPY . /app/src

# Install any needed packages specified in requirements.txt
RUN apt-get update && apt-get install -y \
    libssl-dev \
    && rm -rf /var/lib/apt/lists/*

RUN ls /app/src
# Compile the application
RUN make -C /app/src

# Make port 80 available to the world outside this container
EXPOSE 80

# Run food_coin_program when the container launches
CMD ["./food_coin_program"]

# FROM debian:10

# RUN apt-get update && apt-get install -y \
#     build-essential \
#     libssl-dev


# WORKDIR /app

# # Install the latest version of OpenSSL
# RUN apt-get install -y openssl

# COPY . .

# RUN make
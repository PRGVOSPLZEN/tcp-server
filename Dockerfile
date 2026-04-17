FROM gcc

WORKDIR /server

COPY . .

RUN make

CMD [ "./main.o" ]

EXPOSE 8080
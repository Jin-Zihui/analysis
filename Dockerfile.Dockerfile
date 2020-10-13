FROM gcc:10
WORKDIR /app/
COPY ./* ./
RUN gcc analysis.c -o analysis.out
RUN chmod +x analysis.out
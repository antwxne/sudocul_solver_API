FROM gcc:latest AS builder
WORKDIR /build
RUN apt-get update && apt-get -y install cmake
COPY . .
RUN cmake -B build -DCMAKE_BUILD_TYPE=Debug
RUN cmake --build build

FROM gcc:latest
WORKDIR /app
RUN curl -fsSL https://get.docker.com | sh
COPY --from=builder /build/build/sudocul_solver_api /app/sudocul_solver_api
CMD ["./sudocul_solver_api"]
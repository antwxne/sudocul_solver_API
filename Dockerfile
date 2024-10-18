FROM python:3.12.7-slim 
COPY . .
RUN pip install -r requirements.txt
EXPOSE 8000
ENV PORT=8000
RUN ./manage.py migrate --noinput
CMD ./manage.py runserver 0.0.0.0:$PORT
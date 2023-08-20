# OTP-Display

<h2>Otp display is to show otps on screen. </h2>

Here we are retrieving otps that from Gmail so you would have to use Gmail API. and We are using web server OAuth API <i><b>not the limited input one</b></i>, because it is easy to use. 

1: TO get client_id and client_secret : from google console with "https://www.googleapis.com/auth/gmail.readonly" scope. (if you do not know how to get you can watch  this  <a href="https://www.youtube.com/watch?v=_TjRgW6ViYo">video</a>)

2: Get Refresh token: you have to go to https://developers.google.com/oauthplayground/ to get the Refresh token (we do not need an access token not right know <b>*just Refresh token</b>). 

<h3>Requerments: </h3>
Esp8266 12e,
<a href="https://amzn.eu/d/3bl9i0p">Display</a>,You have to label your otp email. 

<h1>Sketch explaned:</h1>
<h3>refreshgoogletoken() : </h3> <h4> this function is used to refres/Get access token for Gmail api requests.</h4>
<h3>getlestdata() : </h3> <h4> this function is used to Get email id (id: every email has a special number called id not email id).</h4>
<h3>getlestdata() : </h3> <h4> this function is used to Get email id (id: every email has a special number called id not email id).</h4>

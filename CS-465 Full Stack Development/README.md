## <u>CS-465 Full Stack Development</u>
<dd>
    Learned and exercised designing and developing full stack applications using programming language frameworks.  Created a database and
    developed the code to interface it with an application
</dd>
<dl>
    <dt><h4><u>Projects Overview</u></h4></dt>
  <dd>
      The project in this course used NodeJS, Express, MongoDB and Angular to develop a full stack application with a finished admin site including authentication. 
</dd>

* Used Express to create a static web site and api server.
* Created a MongoDB database and interfaced it with admin and customer sites.
* Developed admin site using Angular and leveraged MongoDB to store information used on site.

---

# Module 8-1  
## Architecture  

* **Compare and contrast the types of frontend development you used in your full stack project, including Express HTML, JavaScript, and the single-page application (SPA).**  

   Express framework was used as the web server to serve the web pages for the static HTML site.  Angular was used on the admin site which is a single-page application and utilized the mongoose framework for interacting with the MongoDB database.  JavaScript was used on both the client-side site and the admin site to dynamically interact with HTML elements.

* **Why did the backend use a NoSQL MongoDB database?**  

   MongoDB was used because it is lightweight, easy to implement with Angular, Express, NodeJS and JavaScript, and because of its ability to scale. 

## Functionality

* **How is JSON different from Javascript and how does JSON tie together the frontend and backend development pieces?**
   JSON is used 
   
   JavaScript is a programming language used in most websites.  While both JSON and JavaScript objects store data, JavaScript can only be used in JavaScript while JSON is independent of any programming language.  In our application, JSON is used to render the information shown in the static HTML pages of the client facing site, on the backend it is used to supply the database schema to the MongoDB and seed the database with a set of default records.
   
* **Provide instances in the full stack process when you refactored code to improve functionality and efficiencies, and name the benefits that come from reusable user interface (UI) components.**

   An example of when I refactored code to improve functionality and efficiency would be the refactorization of the trip listing to use MongoDB and making use of cards to show the trips.  By showing trips as a card makes them more aesthically pleasing and more functional.  Using static HTML and JSON to render the page makes it more difficult to change the content whereas utilizing MongoDB and Angular to create modules reduces the size of an application and reduces the amount of errors encountered while making it more efficient.

## Testing

* **Methods for request and retrieval necessitate various types of API testing of endpoints, in addition to the difficulties of testing with added layers of security. Explain your understanding of methods, endpoints, and security in a full stack application.**

   One method of testing an API is with the use of an application like Postman.  Such software allows for testing just about every aspect of an API, even after security has been implemented.  Making use of frameworks like JSON Web Tokens one can test authentication by simulating login, register and logout functionality.  Methods are the server-side actions used to provide authentication and registration to users.  Endpoints are the individual assets in which users access a web application.  Security is which is used to restrict access to certain web resources without valid authentication.  Another way of providing security is to separate a web application using middleware and making use of an API server.

## Reflection

* **How has this course helped you in reaching your professional goals? What skills have you learned, developed, or mastered in this course to help you become a more marketable candidate in your career field?**

   This course taught me how to use Angular at a basic level which only adds to my skills which ultimately helps me reach my professional goals.  Using MongoDB throughout this course allowed me to strengthen my skills on MongoDB.  The knowledge gained from this course most definitely makes me more marketable in my career field.

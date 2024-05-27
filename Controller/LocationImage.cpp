//
// Created by Kamil Krawczyk on 11/05/2024.
//

#include "LocationImage.h"

LocationImage::LocationImage(std::string name) {
    std::string url = "https://www.googleapis.com/customsearch/v1?q=" + name + "+city+from+birds+eye+view" + "&cx=" + GOOGLE_CUSTOM_SEARCH_ENGINE_ID + "&num=1&searchType=image&key=" + GOOGLE_API_KEY;
//    FetchAPI api(url);
//    HandleJson data(api.fetchedData);
    
//    std::string  imageUrl = data.content["items"][0]["link"];
//    sf::Http::Request request("biala-tarnowska.org/wp-content/uploads/2019/01/slajd7.jpg", sf::Http::Request::Get);
//    sf::Http http("http://i0.wp.com");
//    sf::Http::Response response = http.sendRequest(request);

    // check the status
//    if (response.getStatus() == sf::Http::Response::Ok)
//    {
        // check the contents of the response

        
//        std::ofstream imageFile;
//        imageFile.open("X.jpg", std::ios::binary);
//        imageFile.write(response.getBody().data().c_str(), response.getBody().size());
//        imageFile.close();

//        sf::Image image;
//        if (!image.loadFromFile("x.jpg")) {
//            // error handling
//        }
//        sf::Texture texture;
//        if (!texture.loadFromMemory(response.getBody().c_str(), response.getBody().size())) {
//            // error handling
//        }
//        sprite.setTexture(texture);
//        
//    }
}
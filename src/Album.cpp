//
// Created by Michael Wittmann on 08/05/2020.
//

#include "Album.hpp"

spotify::Page<spotify::Album> spotify::v1::Album::get_artist_albums(std::string_view artist_id) {
    auto local_future = stlab::async(stlab::default_executor, spotify::detail::HttpHelper::get1,
                                     "https://api.spotify.com/v1/artists/" + std::string(artist_id) + "/albums")
                        | ([](std::string_view s) { return json_t::parse(s); })
                        | ([](const json_t &j) { return j.get<spotify::model::album>(); });
    auto local_obj = stlab::blocking_get(local_future);
    return spotify::Page<spotify::Album>();
}
/*
 *  public static async Task<Page<Album>> GetArtistAlbums(string artistId)
        {
            var json = await HttpHelper.Get("https://api.spotify.com/v1/artists/" + artistId + "/albums");
            var obj = JsonConvert.DeserializeObject<page<album>>(json, new JsonSerializerSettings
                {
                    TypeNameHandling = TypeNameHandling.All,
                    TypeNameAssemblyFormat = System.Runtime.Serialization.Formatters.FormatterAssemblyStyle.Simple
                });

            return obj.ToPOCO<Album>();
        }
 */
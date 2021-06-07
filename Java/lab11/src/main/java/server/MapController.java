package server;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.annotation.PostConstruct;
import java.io.IOException;
import java.io.Serializable;
import java.util.HashMap;


@Controller
public class MapController implements Serializable {
   HashMap<Integer, String> map = new HashMap<>();
    Writer writer = new Writer();

    @GetMapping("/")
    public String indexPage(Model model) throws IOException {

        model.addAttribute("collection", map);

        if(map.size() != 0)
            writer.save(map);

        return "index";
    }

    @PostMapping("/change")
    public String mapValueChange(@RequestParam Integer key, @RequestParam String value, Model model)
    {
        map.put(key, value);

        return "redirect:/";
    }

    @PostConstruct
    public final void start()
    {
        var init = writer.init();

        if(init != null && init.size() != 0)
            map = init;
    }

    public void finish() throws IOException {

    }


}

// http://localhost:8080/change?key=6&value=%22Hello%22